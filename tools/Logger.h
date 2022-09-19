#ifndef DISK_TOOLS_LOGGER_H_
#define DISK_TOOLS_LOGGER_H_

#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#define LOG(lvl) BOOST_LOG_TRIVIAL(lvl)

namespace logging = boost::log;
void init_logger();

#endif //DISK_TOOLS_LOGGER_H_
