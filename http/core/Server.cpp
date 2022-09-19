#include "Server.h"
#include "../../tools/Config.h"
#include "../api/Router.h"

void server_run() {

  auto config = Config::get_instance();
  unsigned short threads = config->n_threads;
  unsigned short port = config->port;
  std::string address = config->address;

  Router::do_open();
  net::io_context ioc{threads};

  std::make_shared<Listener>(
      ioc,
      tcp::endpoint{net::ip::make_address(address), port}
  )->run();

  LOG(info) << "server started";

  std::vector<std::thread> v;
  v.reserve(threads - 1);
  for (auto i = threads - 1; i > 0; --i)
    v.emplace_back(
        [&ioc] {
          ioc.run();
        });
  ioc.run();

  LOG(info) << "server stopped";
}

void signal_handler(int sig_num) {
  Router::do_close();
  exit(sig_num);
}