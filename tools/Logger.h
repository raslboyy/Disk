#ifndef DISK_TOOLS_LOGGER_H_
#define DISK_TOOLS_LOGGER_H_

#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace logging = boost::log;
BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, logging::sources::logger_mt)
void init_logger();
/// <summary>log(logging::trivial::info, "invalid request");
/// </summary>
inline void log(logging::trivial::severity_level type, std::string &&message) {
  auto lg = my_logger::get();
  BOOST_LOG_SEV(lg, type) << message;
}

#endif //DISK_TOOLS_LOGGER_H_
