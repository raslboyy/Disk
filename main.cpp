#include "http/core/Server.h"
#include "tools/Logger.h"

int main(int argc, char *argv[]) {

  signal(SIGTERM, signal_handler);

  init_logger();
  logging::add_common_attributes();

  server_run();

  return 0;
}