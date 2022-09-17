#include "SystemItemList.h"

#include <unordered_map>

SystemItemList::SystemItemList(const SystemItemImportRequest &items)
    : date(items.updateDate) {
  for (const auto &item : items.items)
    this->items.push_back(std::move(SystemItem{item, items.updateDate}));
}

bool SystemItemList::has_same_id() const {
  std::unordered_map<std::string_view, int> counter;
  for (const auto &item : items) {
    counter[item.id()]++;
    if (counter[item.id()] == 2)
      return true;
  }
  return false;
}