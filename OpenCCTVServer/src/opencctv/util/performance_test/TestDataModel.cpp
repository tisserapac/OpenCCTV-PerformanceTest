/*
 * TestDataModel.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: anjana
 */

#include "TestDataModel.hpp"

namespace opencctv {
namespace util {
namespace performance_test {

TestDataModel* TestDataModel::_pModel = NULL;

TestDataModel::TestDataModel()
{
	_timer = NULL;
}

TestDataModel* TestDataModel::getInstance() {
	if (!_pModel) {
		_pModel = new TestDataModel();

	}
	return _pModel;
}

util::performance_test::Timer*& TestDataModel::getTimer(){
	return _timer;
}

void TestDataModel::setTimer(util::performance_test::Timer*& timer) {
	_timer = timer;
}

TestDataModel::~TestDataModel()
{
	delete _pModel; _pModel = NULL;
}

} /* namespace performance_test */
} /* namespace util */
} /* namespace opencctv */
