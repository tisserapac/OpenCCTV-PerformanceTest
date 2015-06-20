/*
 * StreamTimer.hpp
 *
 *  Created on: Jun 16, 2015
 *      Author: anjana
 */

#include <iostream>
#include <fstream>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include "DateTime.hpp"

#ifndef STREAMTIMER_HPP_
#define STREAMTIMER_HPP_

namespace opencctv {
namespace util {
namespace performance_test {

class StreamTimer {
private:
	boost::mutex _mutex;

	int _iStreamId;
	int _iCount;
	std::string _sLogFileName;

	unsigned long long _lStartTime;
	unsigned long long _lStopTime;

	clock_t _clockStart;
	clock_t _clockStop;

	timespec _timeStartClockTime;
	timespec _timeStopClockTime;

public:
	StreamTimer(int iStreamId, int iCount, std::string sLogFileName);
	virtual ~StreamTimer();

	bool initLogFileEnty();
	bool writeAverageTimes();
	int getCount() const;
	void setCount(int count);
	int getStreamId() const;
	const std::string& getLogFileName() const;
	void setStartTimes();
	void setStopTimes() ;
};

} /* namespace performance_test */
} /* namespace util */
} /* namespace opencctv */

#endif /* STREAMTIMER_HPP_ */
