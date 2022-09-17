#ifndef DISK_SERVICES_TREE_API_VALIDATENODEINTERFACE_H_
#define DISK_SERVICES_TREE_API_VALIDATENODEINTERFACE_H_

#include "../../../entities/model/SystemItemList.h"

struct ValidateNodeInterface {
  virtual bool is_can_be_putted(const SystemItemList &items) = 0;
  virtual bool is_can_be_putted(const SystemItem &item) = 0;
};

#endif //DISK_SERVICES_TREE_API_VALIDATENODEINTERFACE_H_
