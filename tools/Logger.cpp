#include "Logger.h"

#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>

namespace logging = boost::log;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;

void init_logger() {
//  logging::add_file_log("disk.log");
//  logging::core::get()->set_filter
//      (
//          logging::trivial::severity >= logging::trivial::info
//      );
}