#ifndef DISK_HTTP_CONFIG_H_
#define DISK_HTTP_CONFIG_H_

#include <string>
#include <sstream>
#include <fstream>
#include <memory>

#include "json.h"

struct Config {
 private:
  std::string file;
  static std::shared_ptr<Config> singleton_;
  explicit Config(const std::string &f) : file(f) {
    std::ifstream is(f);
    if (is.fail())
      throw std::invalid_argument("config file not found");
    std::stringstream buffer;
    buffer << is.rdbuf();
    JsonValue jv = boost::json::parse(buffer.str());
    try {
      backup_file = jv.at("backup_file").as_string();
      log_file = jv.at("log_file").as_string();
      address = jv.at("address").as_string();
      port = jv.at("port").to_number<uint64_t>();
      n_threads = jv.at("n_treads").to_number<uint64_t>();
    }
    catch (std::exception &) {
      throw std::logic_error("config does not match the structure");
    }
  }
 public:
  Config() = delete;
  Config(const Config &) = delete;
  void operator=(const Config &) = delete;
  static std::shared_ptr<Config> get_instance() {
    if (Config::singleton_ == nullptr)
      Config::singleton_ = std::shared_ptr<Config>(new Config("config.json"));
    return Config::singleton_;
  }

  std::string backup_file;
  std::string log_file;
  std::string address;
  unsigned short port{};
  unsigned short n_threads{};
};

#endif //DISK_HTTP_CONFIG_H_
