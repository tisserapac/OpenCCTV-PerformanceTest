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

} /* namespace performance_test */
} /* namespace util */
} /* namespace opencctv */
