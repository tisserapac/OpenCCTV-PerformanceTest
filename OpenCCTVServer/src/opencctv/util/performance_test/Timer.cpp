/*
 * Timer.cpp
 *
 *  Created on: Jun 21, 2015
 *      Author: anjana
 */

#include "Timer.hpp"

namespace opencctv {
namespace util {
namespace performance_test {

Timer::Timer(int iId, int iCount, std::string sLogFileName)
{
	_iCount = iCount;
	_iId = iId;
	_sLogFileName = sLogFileName;

	_lStartTime = 0ull;
	_lStopTime = 0ull;

	_clockStart = 0;
	_clockStop = 0;
}

bool Timer::initLogFileEnty()
{
	std::ofstream logFile;
	logFile.open (_sLogFileName.c_str(),std::ios_base::app);

	if (logFile.is_open())
	{
		std::string sTime = DateTime::getCurrentDateTime();
		logFile << sTime;
		logFile << "\n\n";
		logFile.close();
	}
	else
	{
		return false;
	}
	return true;
}

bool Timer::writeAverageTimes()
{
	long double lAvgTime = (_lStopTime - _lStartTime)/(long double)_iCount;
	long double lAvgCPUTime1 = (((long double)(_clockStop - _clockStart)*1000)/CLOCKS_PER_SEC)/_iCount;
	//long double lAvgCPUTime2 = DateTime::diffClockTimeMs(_timeStartClockTime,_timeStopClockTime)/_iCount;

	std::ofstream logFile;
	logFile.open (_sLogFileName.c_str(),std::ios_base::app);

	if (logFile.is_open())
	{
		logFile << "AvgTotalTime: " << lAvgTime;
		logFile << " AvgTotalCPUTime-clock(): " << lAvgCPUTime1;
		//logFile << " AvgTotalCPUTime-clock_gettime(): " << lAvgCPUTime2;
		logFile << "\n";
		logFile.close();

	}else
	{
		return false;
	}
	return true;
}

int Timer::getCount() const {
	return _iCount;
}

void Timer::setCount(int count) {
	_iCount = count;
}

int Timer::getStreamId() const {
	return _iId;
}

void Timer::setStartTimes()
{
	_lStartTime = DateTime::getCurrentTimeMs();
	_clockStart = DateTime::getCurrentClock();
	//DateTime::getClockTime(_timeStartClockTime);
}

void Timer::setStopTimes()
{
	_lStopTime = DateTime::getCurrentTimeMs();
	_clockStop = DateTime::getCurrentClock();
	//DateTime::getClockTime(_timeStopClockTime);
}

const std::string& Timer::getLogFileName() const {
	return _sLogFileName;
}

Timer::~Timer()
{
}

} /* namespace performance_test */
} /* namespace util */
} /* namespace opencctv */
