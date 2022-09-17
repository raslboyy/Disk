#include <memory>

#include "Node.h"

SystemItem Node::data() const {
  return data_;
}

void Node::update_date(std::string_view new_date) {
  data_.update_date(new_date);
  if (parent_ != nullptr)
    parent_->update_date(new_date);
}

void Node::update_size(int64_t diff) {
  data_.update_size(data_.size() + diff);
  if (parent_ != nullptr)
    parent_->update_size(diff);
}

bool Node::delete_child(const std::string &id) {
  if (children_.find(id) == children_.end())
    return false;
  children_.erase(id);
  return true;
}

bool Node::put_child(const std::shared_ptr<Node> &node) {
  if (children_.find(node->data().id()) != children_.end())
    return false;
  children_.emplace(node->data().id(), node);
  return true;
}

void Node::get_all_ids(std::vector<std::string> ids) {
  ids.emplace_back(data_.id());
  for (const auto &pair : children_) {
    auto child = pair.second;
    child->get_all_ids(ids);
  }
}

void Node::export_(SystemItemExport &export_item) {
  export_item = SystemItemExport(data_);
  for (const auto &pair : children_) {
    auto child = pair.second;
    export_item.children.push_back(std::move(SystemItemExport()));
    child->export_(export_item.children.back());
  }
}

Node::Node(const SystemItem &item, const std::shared_ptr<Node> &parent)
    : data_(item),
      parent_(parent) {}

void tag_invoke(boost::json::value_from_tag, boost::json::value &jv, const std::shared_ptr<Node> &node) {
  jv = {
      {"data", node->data_},
      {"children", node->children_}
  };
}

std::shared_ptr<Node> tag_invoke(boost::json::value_to_tag<std::shared_ptr<Node>>, const JsonValue &jv) {
  auto node = Node();
  Json const &obj = jv.as_object();
  extract(obj, node.data_, "data");
  extract(obj, node.children_, "children");
  return std::make_shared<Node>(node);
}

template<class T>
void extract(const Json &obj, T &t, std::string key) {
  t = boost::json::value_to<T>(obj.at(key));
}
