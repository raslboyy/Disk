#ifndef DISK_LISTENER_H
#define DISK_LISTENER_H

#include "beast.h"
#include "net.h"
#include <boost/smart_ptr.hpp>

class Listener : public std::enable_shared_from_this<Listener> {
  net::io_context &ioc_;
  tcp::acceptor acceptor_;

  void fail(beast::error_code ec, char const *what);
  void on_accept(beast::error_code ec, tcp::socket socket);

 public:

  Listener(
      net::io_context &ioc,
      tcp::endpoint endpoint);

  void run();
};

#endif //DISK_LISTENER_H
