/*
 * DateTime.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: anjana
 */

#include "DateTime.hpp"

namespace opencctv {
namespace util {
namespace performance_test {

DateTime::DateTime()
{
}

DateTime::~DateTime()
{
}

std::string DateTime::getCurrentDateTime()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
	std::string str(buffer);

	return str;
}

unsigned long long DateTime::getCurrentTimeMs()
{
	unsigned long long ret = 0;
	struct timeval t;
	gettimeofday(&t, NULL);
	ret = (((unsigned long long) t.tv_sec) * 1000)
			+ (((unsigned long long) t.tv_usec) / 1000);
	return ret;
}

clock_t DateTime::getCurrentClock()
{
	return clock();
}

int DateTime::getClockTime(timespec& time)
{
	int result = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time);
	return result;
}

long double DateTime::diffClockTimeMs(const timespec& start, const timespec& end)
{
	unsigned long long CLOCK_PRECISION  = 1E9;

	timespec timeDiff;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		timeDiff.tv_sec = end.tv_sec-start.tv_sec-1;
		timeDiff.tv_nsec = CLOCK_PRECISION+end.tv_nsec-start.tv_nsec;
	} else {
		timeDiff.tv_sec = end.tv_sec-start.tv_sec;
		timeDiff.tv_nsec = end.tv_nsec-start.tv_nsec;
	}

	long double result = (timeDiff.tv_sec*1E3) + (long double)(timeDiff.tv_nsec/1E6);

	return result;
}


} /* namespace performance_test */
} /* namespace util */
} /* namespace opencctv */
