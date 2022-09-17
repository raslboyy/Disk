#ifndef DISK_SERVICES_STORAGE_CORE_TREE_H_
#define DISK_SERVICES_STORAGE_CORE_TREE_H_

#include <memory>

#include "../api/PutNodeInterface.h"
#include "../api/DeleteNodeInterface.h"
#include "../api/GetNodeInterface.h"
#include "Node.h"
#include "Node.h"

class Tree :
    public PutNodeInterface,
    public DeleteNodeInterface,
    public GetNodeInterface {
 public:
  bool put(SystemItemList &&list) override;
  bool delete_(std::string_view id, std::string_view date) override;
  std::shared_ptr<SystemItemExport> get(std::string_view id) override;

  Tree(const Tree &) = delete;
  void operator=(const Tree &) = delete;
  static std::shared_ptr<Tree> get_instance() {
    if (Tree::singleton_ == nullptr)
      Tree::singleton_ = std::shared_ptr<Tree>(new Tree());
    return Tree::singleton_;
  }

  static void save_state();
  static void load_state();

 private:
  Tree() { nodes_.emplace(root_->data().id(), root_); };
  void put_child(const std::shared_ptr<Node> &node, std::string_view date);
  void update(const SystemItem &item, std::string_view date);

  bool contains(std::string_view id) const { return nodes_.find(std::string{id}) != nodes_.end(); }

  std::unordered_map<std::string, std::shared_ptr<Node>> nodes_;
  std::shared_ptr<Node> root_ = std::make_shared<Node>();
  static std::shared_ptr<Tree> singleton_;

  friend void tag_invoke(boost::json::value_from_tag, boost::json::value &jv, const Tree &tree);
  friend std::shared_ptr<Tree> tag_invoke(boost::json::value_to_tag<std::shared_ptr<Tree>>, JsonValue const &jv);
};

#endif //DISK_SERVICES_STORAGE_CORE_TREE_H_