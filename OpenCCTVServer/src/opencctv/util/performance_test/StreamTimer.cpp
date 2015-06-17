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
	_lStartTime = 0;
	_lStopTime = 0;
	//_sLogFileName = "/usr/local/opencctv/performance-test/StreamTimerLog.txt";
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

bool StreamTimer::writeAverageTime()
{
	std::ofstream logFile;
	logFile.open (_sLogFileName.c_str(),std::ios_base::app);

	//unsigned long long lAvgTime = (_lStopTime - _lStartTime) / (unsigned long long)_iCount;

	long double lAvgTime = (_lStopTime - _lStartTime) / (long double)_iCount;

	if (logFile.is_open())
	{
		/*logFile << "Stream Id : " << _iStreamId;
		logFile << " Start Time : " << _lStartTime;
		logFile << " Stop Time : " << _lStopTime;
		logFile << " Count : " << _iCount;
		logFile << " Average Time : " << lAvgTime;
		logFile << "\n\n";
		logFile.close();*/

		logFile << lAvgTime;
		logFile << "\n";
		logFile.close();
	}
	else
	{
		return false;
	}
	return true;
}

unsigned long long StreamTimer::getStartTime() const
{
	return _lStartTime;
}

void StreamTimer::setStartTime()
{
	_lStartTime = DateTime::getCurrentTimeMs();
}

unsigned long long StreamTimer::getStopTime() const
{
	return _lStopTime;
}

void StreamTimer::setStopTime()
{
	_lStopTime = DateTime::getCurrentTimeMs();
}

int StreamTimer::getCount() const {
		return _iCount;
	}

StreamTimer::~StreamTimer()
{
}

} /* namespace performance_test */
} /* namespace util */
} /* namespace opencctv */
