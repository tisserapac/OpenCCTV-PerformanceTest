/*
 * DateTime.hpp
 *
 *  Created on: Jun 16, 2015
 *      Author: anjana
 */

#ifndef DATETIME_HPP_
#define DATETIME_HPP_

#include <sys/time.h>
#include <ctime>
#include <string>

namespace opencctv {
namespace util {
namespace performance_test {

class DateTime {
public:
	DateTime();
	virtual ~DateTime();
	static std::string getCurrentDateTime();
	static unsigned long long getCurrentTimeMs();
};

} /* namespace performance_test */
} /* namespace util */
} /* namespace opencctv */

#endif /* DATETIME_HPP_ */
