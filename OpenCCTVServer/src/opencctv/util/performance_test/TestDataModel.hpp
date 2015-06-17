/*
 * TestDataModel.hpp
 *
 *  Created on: Jun 16, 2015
 *      Author: anjana
 */

#ifndef TESTDATAMODEL_HPP_
#define TESTDATAMODEL_HPP_

#include <map>
#include "StreamTimer.hpp"

namespace opencctv {
namespace util {
namespace performance_test {

class TestDataModel {
private:
	static TestDataModel* _pModel;
	std::map<unsigned int, util::performance_test::StreamTimer*> _mStreamTimers; // Stream ID as key

	TestDataModel();

public:

	static TestDataModel* getInstance();
	bool containsStreamTimer(unsigned int iStreamId);
	std::map<unsigned int, util::performance_test::StreamTimer*>& getStreamTimers();
	virtual ~TestDataModel();
};

} /* namespace performance_test */
} /* namespace util */
} /* namespace opencctv */

#endif /* TESTDATAMODEL_HPP_ */
