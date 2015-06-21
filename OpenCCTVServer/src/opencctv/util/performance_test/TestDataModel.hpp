/*
 * TestDataModel.hpp
 *
 *  Created on: Jun 16, 2015
 *      Author: anjana
 */

#ifndef TESTDATAMODEL_HPP_
#define TESTDATAMODEL_HPP_

#include <map>
#include "Timer.hpp"

namespace opencctv {
namespace util {
namespace performance_test {

class TestDataModel {
private:
	static TestDataModel* _pModel;
	std::map<unsigned int, util::performance_test::Timer*> _mStreamTimers; // Stream ID as key
	std::map<unsigned int, util::performance_test::Timer*> _mResultsTimers; // Analytic instance ID as key

	TestDataModel();

public:

	static TestDataModel* getInstance();
	bool containsStreamTimer(unsigned int iStreamId);
	std::map<unsigned int, util::performance_test::Timer*>& getStreamTimers();
	bool containsResultsTimer(unsigned int iAnalyticInstanceId);
	std::map<unsigned int, util::performance_test::Timer*>& getResultsTimers();
	virtual ~TestDataModel();
};

} /* namespace performance_test */
} /* namespace util */
} /* namespace opencctv */

#endif /* TESTDATAMODEL_HPP_ */
