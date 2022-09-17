#ifndef DISK_ENTITIES_MODEL_SYSTEMITEMLIST_H_
#define DISK_ENTITIES_MODEL_SYSTEMITEMLIST_H_

#include <deque>
#include "SystemItem.h"
#include "../transport/SystemItemImportRequest.h"

struct SystemItemList {
  std::vector<SystemItem> items;
  std::string date;
  explicit SystemItemList(const SystemItemImportRequest &items);
  [[nodiscard]] bool empty() const { return items.empty(); }
  [[nodiscard]] bool has_same_id() const;
};

#endif //DISK_ENTITIES_MODEL_SYSTEMITEMLIST_H_
