/*
 * StreamTimer.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: anjana
 */

#include "StreamTimer.hpp"

namespace opencctv {
namespace util {
namespace performance_test {

StreamTimer::StreamTimer(int iStreamId, int iCount, std::string sLogFileName)
{
	_iCount = iCount;
	_iStreamId = iStreamId;
	_sLogFileName = sLogFileName;

	_lStartTime = 0ull;
	_lStopTime = 0ull;

	_clockStart = 0;
	_clockStop = 0;
}

bool StreamTimer::initLogFileEnty()
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

bool StreamTimer::writeAverageTimes()
{
	long double lAvgTime = (_lStopTime - _lStartTime)/(long double)_iCount;
	long double lAvgCPUTime1 = (((long double)(_clockStop - _clockStart)*1000)/CLOCKS_PER_SEC)/_iCount;
	long double lAvgCPUTime2 = DateTime::diffClockTimeMs(_timeStartClockTime,_timeStopClockTime)/_iCount;

	std::ofstream logFile;
	logFile.open (_sLogFileName.c_str(),std::ios_base::app);

	if (logFile.is_open())
	{
		logFile << "AvgTotalTime: " << lAvgTime;
		logFile << " AvgTotalCPUTime-clock(): " << lAvgCPUTime1;
		logFile << " AvgTotalCPUTime-clock_gettime(): " << lAvgCPUTime2;
		logFile << "\n";
		logFile.close();

	}else
	{
		return false;
	}
	return true;
}

int StreamTimer::getCount() const {
	return _iCount;
}

void StreamTimer::setCount(int count) {
	_iCount = count;
}

int StreamTimer::getStreamId() const {
	return _iStreamId;
}

void StreamTimer::setStartTimes()
{
	_lStartTime = DateTime::getCurrentTimeMs();
	_clockStart = DateTime::getCurrentClock();
	DateTime::getClockTime(_timeStartClockTime);
}

void StreamTimer::setStopTimes()
{
	_lStopTime = DateTime::getCurrentTimeMs();
	_clockStop = DateTime::getCurrentClock();
	DateTime::getClockTime(_timeStopClockTime);
}

const std::string& StreamTimer::getLogFileName() const {
	return _sLogFileName;
}

StreamTimer::~StreamTimer()
{
}

} /* namespace performance_test */
} /* namespace util */
} /* namespace opencctv */
