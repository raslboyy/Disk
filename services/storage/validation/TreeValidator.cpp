#include "TreeValidator.h"
#include "../core/Tree.h"

static const int64_t url_limit_size = 255;

bool TreeValidator::is_can_be_putted(const SystemItemList &items) {
  if (items.has_same_id())
    return false;
  if (std::any_of(items.items.begin(), items.items.end(),
                  [this](auto &item) { return !is_can_be_putted(item); }))
    return false;
  return true;
}

bool TreeValidator::is_can_be_putted(const SystemItem &item) {
  if (item.type() == SystemItemType::FOLDER) {
    if (!item.url().empty())
      return false;
    if (item.size() != 0)
      return false;
  } else {
    if (item.url().size() > url_limit_size)
      return false;
    if (item.size() <= 0)
      return false;
  }

  return true;
}
