#ifndef DISK_SERVICES_TREE_GETNODEINTERFACE_H_
#define DISK_SERVICES_TREE_GETNODEINTERFACE_H_

#include <string>
#include <memory>

#include "../../../entities/transport/SystemItemExport.h"

struct GetNodeInterface {
  virtual std::shared_ptr<SystemItemExport> get(std::string_view id) = 0;
};

#endif //DISK_SERVICES_TREE_GETNODEINTERFACE_H_