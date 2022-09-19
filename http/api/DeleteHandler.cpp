#include "DeleteHandler.h"
#include "../../tools/Time.h"
#include "../../services/storage/core/Tree.h"

static std::string get_id(std::string_view target) {
  auto sub_target = target.substr(8, target.find('?') - 8);
  return std::string{sub_target};
}

static std::string get_date(std::string_view target) {
  auto sub_target = target.substr(target.find("date=") + 5, target.size() - target.find("date=") - 5);
  return std::string{sub_target};
}

static bool validate(std::string_view id, std::string_view date) {
  if (id.empty())
    return false;
  bool successfully = false;
  parse_ISO8601(std::string{date}, successfully);
  if (!successfully)
    return false;
  return true;
}

template<>
RouterResponse DeleteHandler::handle_message<MessageType::delete_>(RouterRequest &&request) {
  RouterResponse response;
  response.status = 200;

  auto id = get_id(request.target);
  auto date = get_date(request.target);
  LOG(debug) << std::string("delete: id=" + id + " date=" + date);

  if (!validate(id, date)) {
    response.status = 400;
    response.body = "Validation Failed";
    LOG(debug) << "delete: validation failed";
    return response;
  }
  LOG(debug) << "delete: validation complete";

  auto deleted = eraser_->delete_(id, date);
  if (!deleted) {
    response.status = 404;
    response.body = "Item not found";
    LOG(debug) << "delete: item not found";
    return response;
  }
  LOG(debug) << "delete: deleted";

  return response;
}

RouterResponse DeleteHandler::handle(RouterRequest &&request) {
  RouterResponse response;
  auto type = request.type;

  if (type == MessageType::delete_) {
    LOG(debug) << "move to delete_child handler";
    response = handle_message<MessageType::delete_>(std::move(request));
  } else {
    LOG(debug) << "move to unknown handler";
  }

  return response;
}

DeleteHandler::DeleteHandler(std::shared_ptr<DeleteNodeInterface> &&eraser)
    : eraser_(std::move(eraser)) {}

DeleteHandler::DeleteHandler() : DeleteHandler(
    std::shared_ptr<DeleteNodeInterface>{Tree::get_instance()}
) {}