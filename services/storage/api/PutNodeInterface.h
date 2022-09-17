#ifndef DISK_SERVICES_TREE_API_PUTNODEINTERFACE_H_
#define DISK_SERVICES_TREE_API_PUTNODEINTERFACE_H_

#include "../../../entities/model/SystemItemList.h"

struct PutNodeInterface {
  virtual bool put(SystemItemList &&list) = 0;
};

#endif //DISK_SERVICES_TREE_API_PUTNODEINTERFACE_H_
