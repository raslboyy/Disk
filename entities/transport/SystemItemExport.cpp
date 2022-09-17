#include "SystemItemExport.h"

#include "../../tools/json.h"

SystemItemExport::SystemItemExport(const SystemItem &item)
    : id(item.id()),
      url(item.url()),
      date(item.date()),
      parentId(item.parentId()),
      type(item.type() == SystemItemType::FILE ? "FILE" : "FOLDER"),
      size(item.size()) {}

// TODO: more beautiful
void tag_invoke(boost::json::value_from_tag, boost::json::value &jv, SystemItemExport const &c) {
  jv = {
      {"id", c.id},
      {"url", c.url},
      {"type", c.type},
      {"parentId", c.parentId},
      {"date", c.date},
      {"size", c.size},
      {"children", c.children}
  };
  if (c.url.empty())
    jv.at("url").emplace_null();
  if (c.parentId.empty())
    jv.at("parentId").emplace_null();
  if (c.type == "FILE")
    jv.at("children").emplace_null();
}
