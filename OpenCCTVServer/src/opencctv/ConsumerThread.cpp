
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
		_pImageMulticaster->start();
	}

	/*=====Begin - For Performance Testing===============*/

	opencctv::util::performance_test::TestDataModel* pModel = opencctv::util::performance_test::TestDataModel::getInstance();
	opencctv::util::performance_test::StreamTimer* pStreamTimer =  pModel->getStreamTimers()[_iStreamId];
	pStreamTimer->setStopTime();
	pStreamTimer->writeAverageTime();

	/*=====End - For Performance Testing=================*/

	opencctv::util::log::Loggers::getDefaultLogger()->info("Consumer Thread stopped.");
}

} /* namespace opencctv */
