
#include "ConsumerThread.hpp"

namespace opencctv {

ConsumerThread::ConsumerThread(unsigned int iStreamId, ImageMulticaster* pImageMulticaster) {
	ApplicationModel* pModel = ApplicationModel::getInstance();
	_pQueue = NULL;
	if(pModel->containsInternalQueue(iStreamId))
	{
		_pQueue = pModel->getInternalQueues()[iStreamId];
	}
	_pImageMulticaster = pImageMulticaster;
	_iStreamId = iStreamId;
}

void ConsumerThread::operator ()()
{
	if(_pImageMulticaster)
	{
		opencctv::util::log::Loggers::getDefaultLogger()->info("Consumer Thread started.");

		/*=====Begin - For Performance Testing===============*/

		opencctv::util::performance_test::TestDataModel* pTestDataModel = opencctv::util::performance_test::TestDataModel::getInstance();
		opencctv::util::performance_test::StreamTimer* pStreamTimer = NULL;
		if(pTestDataModel->containsStreamTimer(_iStreamId))
		{
			pStreamTimer =  pTestDataModel->getStreamTimers()[_iStreamId];
		}
		/*=====End - For Performance Testing=================*/

		_pImageMulticaster->start();

		if(pStreamTimer) //For Performance Testing
		{
			pStreamTimer->setStopTimes();
			pStreamTimer->writeAverageTimes();
		}
	}

	opencctv::util::log::Loggers::getDefaultLogger()->info("Consumer Thread stopped.");
}

} /* namespace opencctv */
