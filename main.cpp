#include "http/core/Server.h"
#include "tools/Logger.h"
#include "tools/Config.h"

void setup() {
  // TODO: kill handler
  signal(SIGTERM, signal_handler);

  init_logger();
  logging::add_common_attributes();

  Config::get_instance();
  LOG(info) << "config loaded successfully";
}

int main(int argc, char *argv[]) {

  setup();

  server_run();

  return 0;
}