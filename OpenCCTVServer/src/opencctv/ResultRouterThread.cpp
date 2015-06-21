
#include "ResultRouterThread.hpp"

namespace opencctv {

ResultRouterThread::ResultRouterThread(unsigned int iAnalyticInstanceId) {
	ApplicationModel* pModel = ApplicationModel::getInstance();
	_pFlowController = NULL;
	if(pModel->containsFlowController(iAnalyticInstanceId))
	{
		_pFlowController = pModel->getFlowControllers()[iAnalyticInstanceId];
	}
	_pSerializer = util::serialization::Serializers::getInstanceOfDefaultSerializer();
	_iAnalyticInstanceId = iAnalyticInstanceId;
}

void ResultRouterThread::operator()()
{
	util::Config* pConfig = util::Config::getInstance();
	ApplicationModel* pModel = ApplicationModel::getInstance();
	if(pModel->containsResultsOutputQueueAddress(_iAnalyticInstanceId))
	{
		//Initialize the ZMQ connection to the analytic instance's output queue
		bool bConnected = false;
		mq::TcpMqReceiver receiver;
		try
		{
			receiver.connectToMq(pConfig->get(util::PROPERTY_ANALYTIC_SERVER_IP), pModel->getResultsOutputQueueAddresses()[_iAnalyticInstanceId]);
			bConnected = true;
		}
		catch(Exception &e)
		{
			std::string sErrMsg = "Failed to connect to Analytic Output Queue. ";
			sErrMsg.append(e.what());
			util::log::Loggers::getDefaultLogger()->error(sErrMsg);
		}

		//Create the AnalyticResultGateway to the DB
		opencctv::db::AnalyticResultGateway* _pAnalyticResultGateway = NULL;
		try
		{
			_pAnalyticResultGateway = new opencctv::db::AnalyticResultGateway();

		}catch(opencctv::Exception &e)
		{
			util::log::Loggers::getDefaultLogger()->error(e.what());
		}

		//Start inserting the analytic instance's results to the results DB

		/*=====Begin - For Performance Testing===============*/

		opencctv::util::performance_test::TestDataModel* pTestDataModel = opencctv::util::performance_test::TestDataModel::getInstance();
		opencctv::util::performance_test::Timer* pResultsTimer = NULL;
		int iCount = 0;
		if(pTestDataModel->containsResultsTimer(_iAnalyticInstanceId))
		{
			pResultsTimer =  pTestDataModel->getStreamTimers()[_iAnalyticInstanceId];
			iCount = pTestDataModel->getStreamTimers()[_iAnalyticInstanceId]->getCount();
		}
		/*=====End - For Performance Testing=================*/

		if(pResultsTimer) //For Performance Testing
		{
			pResultsTimer->setStartTimes();
		}

		int i = 0;

		//while(bConnected && _pFlowController && _pAnalyticResultGateway)
		while(i<iCount && bConnected && _pFlowController && _pAnalyticResultGateway) //For Performance Testing
		{
			std::string* pSSerializedResult = receiver.receive();
			analytic::AnalyticResult result = _pSerializer->deserializeAnalyticResult(*pSSerializedResult);
			std::string sMsg = "\t\tReceived Result of ";
			sMsg.append(result.getTimestamp());
			util::log::Loggers::getDefaultLogger()->debug(sMsg);

			//Saving to DB
			if(result.getWriteToDatabase())
			{
				try
				{
					(*_pAnalyticResultGateway).insertResults(_iAnalyticInstanceId, result);
					//sMsg = "\t\t\tResult written to the database";
					util::log::Loggers::getDefaultLogger()->debug(sMsg);

				}catch(opencctv::Exception &e)
				{
					std::ostringstream sErrorMessage;
					sErrorMessage << "Failed to write results to the results database : analytic id - ";
					sErrorMessage << _iAnalyticInstanceId;
					sMsg = sErrorMessage.str();
					util::log::Loggers::getDefaultLogger()->error(sMsg);
				}
			}

			_pFlowController->received();
			if(pSSerializedResult) delete pSSerializedResult;
		}

		if(pResultsTimer) //For Performance Testing
		{
			pResultsTimer->setStopTimes();
			pResultsTimer->writeAverageTimes();
		}
	}
	opencctv::util::log::Loggers::getDefaultLogger()->info("Results Router Thread stopped.");
}

} /* namespace opencctv */
