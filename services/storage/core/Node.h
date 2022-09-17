#ifndef DISK_SERVICES_STORAGE_CORE_NODE_H_
#define DISK_SERVICES_STORAGE_CORE_NODE_H_

#include "../../../entities/model/SystemItem.h"
#include "../../../entities/transport/SystemItemExport.h"

class Node {
 public:
  SystemItem data() const;
  SystemItem &data() { return data_; }
  void update_date(std::string_view new_date);
  void update_size(int64_t diff);
  bool delete_child(const std::string &id);
  bool put_child(const std::shared_ptr<Node> &node);
  void get_all_ids(std::vector<std::string> ids);
  void export_(SystemItemExport &export_item);

  explicit Node(const SystemItem &item, const std::shared_ptr<Node> &parent);
  Node() = default;

  friend void tag_invoke(boost::json::value_from_tag, boost::json::value &jv, const std::shared_ptr<Node> &node);
  friend std::shared_ptr<Node> tag_invoke(boost::json::value_to_tag<std::shared_ptr<Node>>, JsonValue const &jv);
 private:

  SystemItem data_;
  std::unordered_map<std::string, std::shared_ptr<Node>> children_;
  std::shared_ptr<Node> parent_;
};

#endif //DISK_SERVICES_STORAGE_CORE_NODE_H_
