#ifndef DISK_API_CONTROLLER_ROUTER_H_
#define DISK_API_CONTROLLER_ROUTER_H_

#include "../core/beast.h"
#include "../../tools/Logger.h"

using MessageType = http::verb;

struct RouterResponse {
  unsigned int status;
  std::string body;
};

struct RouterRequest {
  MessageType type;
  std::string target;
  std::string body;
};

namespace Router {

RouterResponse send_request(RouterRequest &&request);

void do_close();
void do_open();

};

#endif //DISK_API_CONTROLLER_ROUTER_H_
