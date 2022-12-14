#include "Router.h"
#include "ImportsHandler.h"
#include "DeleteHandler.h"
#include "NodesHandler.h"
#include "../../services/storage/core/Tree.h"

#include <string>
#include <unordered_map>

namespace Router {

bool arg1_is_arg2_prefix(std::string_view prefix, std::string_view word) {
  return std::mismatch(prefix.begin(), prefix.end(), word.begin()).first == prefix.end();
}

RouterResponse send_request(RouterRequest &&request) {
  LOG(debug) << "request: " + request.target + "\n" + request.body;

  std::unordered_map<std::string_view, HandlerInterface *> mapping;
  RouterResponse response;
  std::string_view target = request.target;
  const std::string imports = "/imports";
  mapping[imports] = new ImportsHandler();
  const std::string delete_ = "/delete";
  mapping[delete_] = new DeleteHandler();
  const std::string nodes = "/nodes";
  mapping[nodes] = new NodesHandler();

  if (arg1_is_arg2_prefix(imports, target)) {
    LOG(debug) << "move to imports handler";
    response = mapping[imports]->handle(std::move(request));
  } else if (arg1_is_arg2_prefix(delete_, target)) {
    LOG(debug) << "move to delete handler";
    response = mapping[delete_]->handle(std::move(request));
  } else if (arg1_is_arg2_prefix(nodes, target)) {
    LOG(debug) << "move to nodes handler";
    response = mapping[nodes]->handle(std::move(request));
  } else {
    LOG(debug) << "move to unknown handler";
    response.status = 501;
  }

  LOG(debug) << "response: " + std::to_string(response.status) + "\n" + response.body;
  return response;
}

void do_close() {
  LOG(info) << "saving state";
  Tree::save_state();
}

void do_open() {
  LOG(info) << "loading state";
  Tree::load_state();
}

};