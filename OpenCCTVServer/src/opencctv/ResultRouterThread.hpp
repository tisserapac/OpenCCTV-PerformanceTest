
#ifndef OPENCCTV_RESULTROUTERTHREAD_HPP_
#define OPENCCTV_RESULTROUTERTHREAD_HPP_

#include <sstream>
#include "ApplicationModel.hpp"
#include "mq/TcpMqReceiver.hpp"
#include "util/Config.hpp"
#include "Exception.hpp"
#include "util/log/Loggers.hpp"
#include "util/serialization/Serializers.hpp"
#include "db/AnalyticResultGateway.hpp"
#include "util/performance_test/TestDataModel.hpp"

namespace opencctv {

class ResultRouterThread {
private:
	util::flow::FlowController* _pFlowController;
	unsigned int _iAnalyticInstanceId;
	util::serialization::Serializable* _pSerializer;
	unsigned int _iTimerId;//For performance Testing

public:
	//ResultRouterThread(unsigned int iAnalyticInstanceId);
	ResultRouterThread(unsigned int iAnalyticInstanceId, unsigned int iTimerId = 0);//For performance testing
	void operator()();
};

} /* namespace opencctv */

#endif /* OPENCCTV_RESULTROUTERTHREAD_HPP_ */
