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
	util::performance_test::Timer* _timer;

	TestDataModel();

public:

	static TestDataModel* getInstance();
	util::performance_test::Timer*& getTimer();
	void setTimer(util::performance_test::Timer*& timer);
	virtual ~TestDataModel();
};

} /* namespace performance_test */
} /* namespace util */
} /* namespace opencctv */

#endif /* TESTDATAMODEL_HPP_ */
