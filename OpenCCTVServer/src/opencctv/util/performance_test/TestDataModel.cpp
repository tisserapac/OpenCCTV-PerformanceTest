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
}

TestDataModel* TestDataModel::getInstance() {
	if (!_pModel) {
		_pModel = new TestDataModel();
	}
	return _pModel;
}

std::map<unsigned int, util::performance_test::Timer*>& TestDataModel::getTimers()
{
	return _mTimers;
}

bool TestDataModel::containsTimer(unsigned int iTimerId)
{
	std::map<unsigned int, util::performance_test::Timer*>::iterator it = _mTimers.find(iTimerId);
	if(it != _mTimers.end())
	{
		return true;
	}
	return false;
}

TestDataModel::~TestDataModel()
{
	delete _pModel; _pModel = NULL;
}

} /* namespace performance_test */
} /* namespace util */
} /* namespace opencctv */
