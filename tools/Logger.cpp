#include "Logger.h"
#include "Config.h"

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>

void init_logger() {
  logging::add_file_log(Config::get_instance()->log_file);
  logging::core::get()->set_filter
      (
          logging::trivial::severity >= logging::trivial::info
      );
}