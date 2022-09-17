
#include "SystemItem.h"
#include "../../tools/Time.h"

SystemItem::SystemItem(const SystemItemImport &system_item_import, std::string_view date)
    : id_(system_item_import.id),
      url_(system_item_import.url),
      date_(date),
      parentId_(system_item_import.parentId),
      type_(system_item_import.type == "FILE" ? SystemItemType::FILE : SystemItemType::FOLDER),
      size_(system_item_import.size) {}

void SystemItem::update(const SystemItem &item) {
  update_date(item.date());
  update_parentId(item.parentId());
  update_url(item.url());
  if (type_ == SystemItemType::FILE)
    update_size(item.size());
}

void tag_invoke(boost::json::value_from_tag, boost::json::value &jv, const SystemItem &item) {
  jv = {
      {"id", item.id_},
      {"url", item.url_},
      {"date", item.date_},
      {"parentId", item.parentId_},
      {"type", (item.type_ == SystemItemType::FILE ? "FILE" : "FOLDER")},
      {"size", item.size_},
  };
}

SystemItem tag_invoke(boost::json::value_to_tag<SystemItem>, JsonValue const &jv) {
  auto item = SystemItem();
  Json const &obj = jv.as_object();
  extract(obj, item.id_, "id");
  extract(obj, item.url_, "url");
  extract(obj, item.date_, "date");
  extract(obj, item.parentId_, "parentId");
  std::string type;
  extract(obj, type, "type");
  item.type_ = (type == "FILE" ? SystemItemType::FILE : SystemItemType::FOLDER);
  extract(obj, item.size_, "size");
  return item;
}

template<class T>
void extract(const Json &obj, T &t, std::string key) {
  t = boost::json::value_to<T>(obj.at(key));
}