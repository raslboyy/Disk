#include <iostream>

#include "Listener.h"
#include "Http_session.h"
#include "../api/Router.h"

Listener::Listener(
    net::io_context &ioc,
    tcp::endpoint endpoint)
    : ioc_(ioc), acceptor_(net::make_strand(ioc)) {
  beast::error_code ec;

  acceptor_.open(endpoint.protocol(), ec);
  if (ec) {
    fail(ec, "open");
    return;
  }

  acceptor_.set_option(net::socket_base::reuse_address(true), ec);
  if (ec) {
    fail(ec, "set_option");
    return;
  }

  acceptor_.bind(endpoint, ec);
  if (ec) {
    fail(ec, "bind");
    return;
  }

  acceptor_.listen(net::socket_base::max_listen_connections, ec);
  if (ec) {
    fail(ec, "listen");
    return;
  }
}

void Listener::fail(beast::error_code ec, const char *what) {
  Router::do_close();
  if (ec == net::error::operation_aborted)
    return;
  std::cerr << what << ": " << ec.message() << std::endl;
}

void Listener::run() {
  acceptor_.async_accept(
      net::make_strand(ioc_),
      beast::bind_front_handler(
          &Listener::on_accept,
          shared_from_this()));
}
void Listener::on_accept(beast::error_code ec, tcp::socket socket) {
  if (ec)
    return fail(ec, "accept");
  else
    boost::make_shared<Http_session>(
        std::move(socket))->run();

  acceptor_.async_accept(
      net::make_strand(ioc_),
      beast::bind_front_handler(
          &Listener::on_accept,
          shared_from_this()));
}
