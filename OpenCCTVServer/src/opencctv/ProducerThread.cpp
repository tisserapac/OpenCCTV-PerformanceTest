
#include "ProducerThread.hpp"

namespace opencctv {

//ProducerThread::ProducerThread(unsigned int iStreamId, opencctv::api::VmsConnector* pVmsConn)
ProducerThread::ProducerThread(unsigned int iStreamId, opencctv::api::VmsConnector* pVmsConn,unsigned int iTimerId)//For performance testing
{
	ApplicationModel* pModel = ApplicationModel::getInstance();
	_pQueue = NULL;
	if(pModel->containsInternalQueue(iStreamId))
	{
		_pQueue = pModel->getInternalQueues()[iStreamId];
	}
	_pPluginLoader = NULL;
	if(pModel->containsVmsPluginLoader(iStreamId))
	{
		_pPluginLoader = pModel->getVmsPluginLoaders()[iStreamId];
	}
	_pVmsConn = pVmsConn;
	_bActive = false;
	_iStreamId = iStreamId;
	_iTimerId = iTimerId; //For performance testing
}

void ProducerThread::operator ()()
{
	if(_pVmsConn && _pQueue)
	{
		_bActive = true;
		opencctv::util::log::Loggers::getDefaultLogger()->info("Producer Thread started.");

		/*=====Begin - For Performance Testing===============*/

		/*opencctv::util::performance_test::TestDataModel* pTestDataModel = opencctv::util::performance_test::TestDataModel::getInstance();
		opencctv::util::performance_test::Timer* pTimer = NULL;
		if(pTestDataModel->containsTimer(_iTimerId))
		{
			pTimer =  pTestDataModel->getTimers()[_iTimerId];
		}*/
		/*=====End - For Performance Testing=================*/
		try
		{
			/*if(pTimer) //For Performance Testing
			{
				pTimer->setStartTimes();
			}*/

			_pVmsConn->produceImageObjects(_pQueue);
		}
		catch(std::exception &e)
		{
			_bActive = false;
			std::string sErrMsg = "VMS Connector Plugin's produceImageObjects() function failed. ";
			sErrMsg.append(e.what());
			opencctv::util::log::Loggers::getDefaultLogger()->error(sErrMsg);
		}
	}
	opencctv::util::log::Loggers::getDefaultLogger()->info("Producer Thread stopped.");
}

bool ProducerThread::isStillRunning()
{
	bool bVmsConnectorIsActive = false;
	try
	{
		bVmsConnectorIsActive = _pVmsConn->isStillProducingImages();
	}
	catch(std::exception &e)
	{
		throw Exception(e.what());
	}
	return (bVmsConnectorIsActive && _bActive);
}

} /* namespace opencctv */
