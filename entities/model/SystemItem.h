#ifndef DISK_ENTITIES_MODEL_SYSTEMITEM_H_
#define DISK_ENTITIES_MODEL_SYSTEMITEM_H_

#include <string>

#include "SystemItemType.h"
#include "../transport/SystemItemImport.h"

class SystemItem {
  std::string id_;
  std::string url_;
  std::string date_;
  std::string parentId_;
  SystemItemType type_ = SystemItemType::FOLDER;
  int64_t size_{};
 public:
  SystemItem() = default;
  SystemItem(const SystemItem &) = default;
  SystemItem(const SystemItemImport &system_item_import, std::string_view date);

  [[nodiscard]] std::string id() const { return id_; }
  [[nodiscard]] std::string url() const { return url_; }
  [[nodiscard]] std::string date() const { return date_; }
  [[nodiscard]] std::string parentId() const { return parentId_; }
  [[nodiscard]] SystemItemType type() const { return type_; }
  [[nodiscard]] int64_t size() const { return size_; }
  void update_url(std::string_view url) { url_ = std::string{url}; }
  void update_date(std::string_view date) { date_ = std::string{date}; }
  void update_parentId(std::string_view parentId) { parentId_ = std::string{parentId}; }
  void update_size(int64_t size) { size_ = size; }
  void update(const SystemItem &item);

  friend void tag_invoke(boost::json::value_from_tag, boost::json::value &jv, const SystemItem &item);
  friend SystemItem tag_invoke(boost::json::value_to_tag<SystemItem>, JsonValue const &jv);
};

#endif //DISK_ENTITIES_MODEL_SYSTEMITEM_H_
