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

std::map<unsigned int, util::performance_test::Timer*>& TestDataModel::getStreamTimers()
{
	return _mStreamTimers;
}

bool TestDataModel::containsStreamTimer(unsigned int iStreamId)
{
	std::map<unsigned int, util::performance_test::Timer*>::iterator it = _mStreamTimers.find(iStreamId);
	if(it != _mStreamTimers.end())
	{
		return true;
	}
	return false;
}

bool TestDataModel::containsResultsTimer(unsigned int iAnalyticInstanceId)
{
	std::map<unsigned int, util::performance_test::Timer*>::iterator it = _mResultsTimers.find(iAnalyticInstanceId);
	if(it != _mResultsTimers.end())
	{
		return true;
	}
	return false;
}

std::map<unsigned int, util::performance_test::Timer*>& TestDataModel::getResultsTimers()
{
	return _mResultsTimers;
}

TestDataModel::~TestDataModel()
{
	delete _pModel; _pModel = NULL;
}

} /* namespace performance_test */
} /* namespace util */
} /* namespace opencctv */
