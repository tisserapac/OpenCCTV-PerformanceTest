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

Timer::Timer(unsigned int iImageCount, unsigned int iStreamCount, std::string sLogFileName)
{
	_iImageCount = iImageCount;
	_iStreamCount = iStreamCount;
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
	std::ostringstream osMsg;
	osMsg << "_iImageCount * _iStreamCount = " << _iImageCount * _iStreamCount;
	util::log::Loggers::getDefaultLogger()->debug(osMsg.str());

	long double lAvgTime = (_lStopTime - _lStartTime)/(long double)(_iImageCount * _iStreamCount);
	long double lAvgCPUTime1 = (((long double)(_clockStop - _clockStart)*1000)/CLOCKS_PER_SEC)/(_iImageCount * _iStreamCount);
	//long double lAvgCPUTime2 = DateTime::diffClockTimeMs(_timeStartClockTime,_timeStopClockTime)/(_iImageCount * _iStreamCount);

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

unsigned int Timer::getImageCount() const {
	return _iImageCount;
}

void Timer::setImageCount(unsigned int iImageCount) {
	_iImageCount = iImageCount;
}

unsigned int Timer::getStreamCount() const {
	return _iStreamCount;
}

void Timer::setStreamCount(unsigned int iStreamCount) {
	_iStreamCount = iStreamCount;
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
