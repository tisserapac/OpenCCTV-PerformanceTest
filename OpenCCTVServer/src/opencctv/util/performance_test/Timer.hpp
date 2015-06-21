/*
 * Timer.hpp
 *
 *  Created on: Jun 21, 2015
 *      Author: anjana
 */

#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <iostream>
#include <fstream>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include "DateTime.hpp"

namespace opencctv {
namespace util {
namespace performance_test {

class Timer {
private:
	boost::mutex _mutex;

	int _iId; //The id of the stream, analytic instance etc..
	int _iCount;
	std::string _sLogFileName;

	unsigned long long _lStartTime;
	unsigned long long _lStopTime;

	clock_t _clockStart;
	clock_t _clockStop;

	timespec _timeStartClockTime;
	timespec _timeStopClockTime;
public:
	Timer(int iId, int iCount, std::string sLogFileName);
	virtual ~Timer();

	bool initLogFileEnty();
	bool writeAverageTimes();
	int getCount() const;
	void setCount(int count);
	int getStreamId() const;
	const std::string& getLogFileName() const;
	void setStartTimes();
	void setStopTimes();
};

} /* namespace performance_test */
} /* namespace util */
} /* namespace opencctv */

#endif /* TIMER_HPP_ */
