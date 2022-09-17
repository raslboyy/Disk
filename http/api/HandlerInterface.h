#ifndef DISK_API_CONTROLLER_HANDLERINTERFACE_H_
#define DISK_API_CONTROLLER_HANDLERINTERFACE_H_

#include "Router.h"

class HandlerInterface {
 public:
  virtual RouterResponse handle(RouterRequest &&request) = 0;
};

#endif //DISK_API_CONTROLLER_HANDLERINTERFACE_H_
