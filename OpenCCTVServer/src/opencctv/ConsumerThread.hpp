
#ifndef OPENCCTV_CONSUMERTHREAD_HPP_
#define OPENCCTV_CONSUMERTHREAD_HPP_

#include "ApplicationModel.hpp"
#include "mq/TcpMqSender.hpp"
#include "ImageMulticaster.hpp"
#include <vector>
#include "util/performance_test/TestDataModel.hpp"

namespace opencctv {

class ConsumerThread {
private:
	ImageMulticaster* _pImageMulticaster;
	ConcurrentQueue<Image>* _pQueue;
	int _iStreamId;

public:
	ConsumerThread(unsigned int iStreamId, ImageMulticaster* pImageMulticaster);
	void operator()();
};

} /* namespace opencctv */

#endif /* OPENCCTV_CONSUMERTHREAD_HPP_ */
