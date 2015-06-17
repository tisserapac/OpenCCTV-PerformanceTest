/*
 * StreamTimer.hpp
 *
 *  Created on: Jun 16, 2015
 *      Author: anjana
 */

#include <iostream>
#include <fstream>
#include "DateTime.hpp"

#ifndef STREAMTIMER_HPP_
#define STREAMTIMER_HPP_

namespace opencctv {
namespace util {
namespace performance_test {

class StreamTimer {
private:
	int _iStreamId;
	int _iCount;
	std::string _sLogFileName;
	unsigned long long _lStartTime;
	unsigned long long _lStopTime;


public:
	StreamTimer(int iStreamId, int iCount, std::string sLogFileName);

	bool initLogFileEnty();
	bool writeAverageTime();

	unsigned long long getStartTime() const;
	void setStartTime();
	unsigned long long getStopTime() const;
	void setStopTime();
	int getCount() const;
	virtual ~StreamTimer();


};

} /* namespace performance_test */
} /* namespace util */
} /* namespace opencctv */

#endif /* STREAMTIMER_HPP_ */
