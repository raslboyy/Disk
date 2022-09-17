#include "Http_session.h"
#include "../api/Router.h"

template<class Body, class Allocator, class Send>
void handle_request(
    http::request<Body, http::basic_fields<Allocator>> &&req,
    Send &&send) {

  auto routerResponse = Router::send_request(
      {
          req.method(),
          {req.target().data(), req.target().size()},
          {req.body().data(), req.body().size()}
      }
  );

  http::string_body::value_type body = routerResponse.body;
  auto const size = body.size();
  http::response<http::string_body> res{
      std::piecewise_construct,
      std::make_tuple(std::move(body)),
      std::make_tuple(static_cast<http::status>(routerResponse.status), req.version())
  };
  res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
  res.set(http::field::content_type, "application/json");
  res.content_length(size);
  res.keep_alive(req.keep_alive());
  return send(std::move(res));
}

struct Http_session::send_lambda {
  Http_session &self_;

  explicit
  send_lambda(Http_session &self)
      : self_(self) {
  }

  template<bool isRequest, class Body, class Fields>
  void operator()(http::message<isRequest, Body, Fields> &&msg) const {
    auto sp = boost::make_shared<http::message<isRequest, Body, Fields>>(std::move(msg));
    auto self = self_.shared_from_this();
    http::async_write(
        self_.stream_,
        *sp,
        [self, sp](beast::error_code ec, std::size_t bytes) {
          self->on_write(ec, bytes, sp->need_eof());
        });
  }
};

Http_session::Http_session(tcp::socket &&socket)
    : stream_(std::move(socket)) {}

void Http_session::run() {
  do_read();
}

void Http_session::fail(beast::error_code ec, char const *what) {
  if (ec == net::error::operation_aborted)
    return;

  std::cerr << what << ": " << ec.message() << "\n";
}

void Http_session::do_read() {
  req_ = {};
  parser_.emplace();
  parser_->body_limit(10000);
//  stream_.expires_after(std::chrono::seconds(30));
  http::async_read(
      stream_,
      buffer_,
      parser_->get(),
      beast::bind_front_handler(
          &Http_session::on_read,
          shared_from_this()));
}

void Http_session::on_read(beast::error_code ec, std::size_t) {
  if (ec == http::error::end_of_stream) {
    stream_.socket().shutdown(tcp::socket::shutdown_send, ec);
    return;
  }
  if (ec)
    return fail(ec, "read");

  handle_request(
      parser_->release(),
      send_lambda(*this)
  );
}

void Http_session::on_write(beast::error_code ec, std::size_t, bool close) {
  if (ec)
    return fail(ec, "write");

  if (close) {
    do_close();
    return;
  }

  do_read();
}

void Http_session::do_close() {
  beast::error_code ec;
  stream_.socket().shutdown(tcp::socket::shutdown_send, ec);
}
