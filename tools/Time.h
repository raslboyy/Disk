#ifndef DISK_TOOLS_TIME_H_
#define DISK_TOOLS_TIME_H_

#include <chrono>
#include <sstream>
#include <iomanip>

time_t parse_ISO8601(const std::string &date, bool &successfully);

#endif //DISK_TOOLS_TIME_H_
