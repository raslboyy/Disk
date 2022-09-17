#ifndef DISK_ENTITIES_TRANSPORT_SYSTEMITEMEXPORT_H_
#define DISK_ENTITIES_TRANSPORT_SYSTEMITEMEXPORT_H_

#include <string>
#include <vector>
#include "../model/SystemItemType.h"
#include "../model/SystemItem.h"

struct SystemItemExport {
  explicit SystemItemExport(const SystemItem &item);
  SystemItemExport() = default;

  std::string id;
  std::string url;
  std::string date;
  std::string parentId;
  std::string type;
  int64_t size = 0;
  std::vector<SystemItemExport> children;
};

void tag_invoke(boost::json::value_from_tag, boost::json::value &jv, SystemItemExport const &c);

#endif //DISK_ENTITIES_TRANSPORT_SYSTEMITEMEXPORT_H_
