#ifndef DISK_API_SERVER_HTTP_SESSION_H_
#define DISK_API_SERVER_HTTP_SESSION_H_

#include "beast.h"
#include "net.h"

class Http_session : public boost::enable_shared_from_this<Http_session> {
  beast::tcp_stream stream_;
  beast::flat_buffer buffer_;
  http::request<http::string_body> req_;

  boost::optional<http::request_parser<http::string_body>> parser_;

  struct send_lambda;

  void fail(beast::error_code ec, char const *what);
  void do_read();
  void on_read(beast::error_code ec, std::size_t);
  void on_write(beast::error_code ec, std::size_t, bool close);
  void do_close();

 public:
  explicit Http_session(
      tcp::socket &&socket);

  void run();
};

#endif //DISK_API_SERVER_HTTP_SESSION_H_
