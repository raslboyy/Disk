#include "NodesHandler.h"
#include "../../services/transportation/SerializerServicer.h"
#include "../../services/storage/core/Tree.h"

static std::string get_id(std::string_view target) {
  auto sub_target = target.substr(7, target.size() - 7);
  return std::string{sub_target};
}

static bool validate(std::string_view id) {
  if (id.empty())
    return false;
  return true;
}

template<>
RouterResponse NodesHandler::handle_message<MessageType::get>(RouterRequest &&request) {
  RouterResponse response;
  response.status = 200;

  auto id = get_id(request.target);
  log(logging::trivial::debug, "get: id=" + id);
  if (!validate(id)) {
    response.status = 404;
    response.body = "Validation Failed";
    log(logging::trivial::debug, "get: validation failed");
    return response;
  }
  log(logging::trivial::debug, "get: validation complete");

  auto res = getter_->get(id);
  if (res == nullptr) {
    response.status = 404;
    response.body = "Item not found";
    log(logging::trivial::debug, "get: item not found");
    return response;
  }
  log(logging::trivial::debug, "get: got");

  response.body = serializer_->serialize(*res);
  log(logging::trivial::debug, "get: serialized");

  return response;
}

RouterResponse NodesHandler::handle(RouterRequest &&request) {
  RouterResponse response;
  auto lg = my_logger::get();
  auto type = request.type;

  if (type == MessageType::get) {
    BOOST_LOG_SEV(lg, logging::trivial::debug) << "move to get handler";
    response = handle_message<MessageType::get>(std::move(request));
  } else {
    BOOST_LOG_SEV(lg, logging::trivial::warning) << "move to unknown handler";
  }

  return response;
}

NodesHandler::NodesHandler(std::shared_ptr<SystemItemImportResponseSSI> &&serializer,
                           std::shared_ptr<GetNodeInterface> &&getter)
    : serializer_(std::move(serializer)),
      getter_(std::move(getter)) {}

NodesHandler::NodesHandler() : NodesHandler(
    std::move(std::shared_ptr<SystemItemImportResponseSSI>{new SystemItemImportResponseSSJson()}),
    std::shared_ptr<GetNodeInterface>{Tree::get_instance()}
) {}