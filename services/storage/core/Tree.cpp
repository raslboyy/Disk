#include "Tree.h"
#include "../../../tools/Config.h"

#include <unordered_set>

std::shared_ptr<Tree> Tree::singleton_ = nullptr;

bool Tree::put(SystemItemList &&list) {
  auto date = std::move(list.date);
  auto items = std::move(list.items);

  std::unordered_set<std::string> ids_in_list;
  for (const auto &item : items) {
    if (contains(item.id()) && item.type() != nodes_[item.id()]->data().type())
      return false;
    ids_in_list.emplace(item.id());
  }
  for (const auto &item : items)
    if (ids_in_list.find(item.parentId()) == ids_in_list.end() && !contains(item.parentId()))
      return false;

  int already_putted_count = 0;
  while (already_putted_count != items.size()) {
    for (const auto &item : items)
      if (contains(item.parentId())) {
        already_putted_count++;
        if (!contains(item.id()))
          put_child(std::make_shared<Node>(item, nodes_[item.parentId()]), date);
        else
          update(item, date);
      }
  }
  return true;
}

void Tree::put_child(const std::shared_ptr<Node> &node, std::string_view date) {
  auto id = node->data().id();
  auto parent_id = node->data().parentId();
  auto parent_node = nodes_[parent_id];
  parent_node->put_child(node);
  nodes_.emplace(id, node);
  parent_node->update_size(node->data().size());
  parent_node->update_date(date);
}

void Tree::update(const SystemItem &item, std::string_view date) {
  auto item_node = nodes_[item.id()];
  auto old_parent_id = item_node->data().parentId();
  auto new_parent_id = item.parentId();
  auto old_parent_node = nodes_[old_parent_id];
  auto new_parent_node = nodes_[new_parent_id];

  delete_(item.id(), date);
  item_node->data().update(item);
  item_node->update_date(date);
  put_child(item_node, date);
}

bool Tree::delete_(std::string_view id, std::string_view date) {
  if (nodes_.find(std::string{id}) == nodes_.end())
    return false;
  auto node = nodes_[std::string{id}];
  auto parent_node = nodes_[node->data().parentId()];
  parent_node->delete_child(std::string{id});
  parent_node->update_size(-node->data().size());
  parent_node->update_date(date);

  std::vector<std::string> sub_tree;
  node->get_all_ids(sub_tree);
  for (const auto &it : sub_tree)
    nodes_.erase(it);

  return true;
}

std::shared_ptr<SystemItemExport> Tree::get(std::string_view id) {
  if (!contains(std::string{id}))
    return nullptr;
  auto node = nodes_[std::string{id}];
  auto result = std::make_shared<SystemItemExport>();
  node->export_(*result);
  return result;
}

// TODO: do more beautiful json serialization

void tag_invoke(boost::json::value_from_tag, boost::json::value &jv, const Tree &tree) {
  jv = {
      {"root", tree.root_},
      {"nodes", tree.nodes_}
  };
}

void Tree::save_state() {
  if (Tree::singleton_ == nullptr)
    return;
  std::string state = boost::json::serialize(boost::json::value_from(*Tree::singleton_));
  std::ofstream os(Config::get_instance()->backup_file);
  os << state;
}

std::shared_ptr<Tree> tag_invoke(boost::json::value_to_tag<std::shared_ptr<Tree>>, JsonValue const &jv) {
  auto tree = std::shared_ptr<Tree>(new Tree());
  Json const &obj = jv.as_object();
  extract(obj, tree->root_, "root");
  extract(obj, tree->nodes_, "nodes");
  return tree;
}

template<class T>
void extract(const Json &obj, T &t, std::string key) {
  t = boost::json::value_to<T>(obj.at(key));
}

void Tree::load_state() {
  std::ifstream is(Config::get_instance()->backup_file);
  if (is.fail())
    return;
  std::stringstream buffer;
  buffer << is.rdbuf();
  JsonValue jv = boost::json::parse(buffer.str());
  Tree::singleton_ = boost::json::value_to<std::shared_ptr<Tree>>(jv);
}