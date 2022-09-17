#ifndef DISK_SERVICES_STORAGE_CORE_TREEVALIDATOR_H_
#define DISK_SERVICES_STORAGE_CORE_TREEVALIDATOR_H_

#include "../api/ValidateNodeInterface.h"

class TreeValidator : public ValidateNodeInterface {
 public:
  bool is_can_be_putted(const SystemItemList &items) override;
  bool is_can_be_putted(const SystemItem &item) override;
};

#endif //DISK_SERVICES_STORAGE_CORE_TREEVALIDATOR_H_
