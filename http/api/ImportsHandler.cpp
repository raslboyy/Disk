#include <sstream>

#include "ImportsHandler.h"
#include "../../services/transportation/DeserializerService.h"
#include "../../services/storage/core/Tree.h"
#include "../../services/storage/validation/TreeValidator.h"

#include <boost/property_tree/json_parser.hpp>

static const unsigned int invalid_request = 400;
static const unsigned int valid_request = 200;

// TODO: move this and reformat (КОСТЫЛЬ)
static bool fast_json_check(std::string_view json) {
  try {
    boost::property_tree::ptree propertyTree;
    std::stringstream ss;
    ss << json;
    boost::property_tree::read_json(ss, propertyTree);
  }
  catch (boost::property_tree::json_parser_error) {
    return false;
  }
  return true;
}

template<>
RouterResponse ImportsHandler::handle_message<MessageType::post>(RouterRequest &&request) {
  RouterResponse response;
  response.status = invalid_request;
  response.body = "Validation Failed";

  if (!fast_json_check(request.body)) {
    log(logging::trivial::info, "invalid json in request");
    return response;
  }

  SystemItemImportRequest system_item_import_request(std::move(deserializer_->deserialize(request.body)));
  log(logging::trivial::debug, "request deserialized");

  if (!raw_validator_->validate(system_item_import_request)) {
    log(logging::trivial::info, "invalid request");
    return response;
  }
  log(logging::trivial::debug, "request completed raw validation");

  auto system_item_list = SystemItemList(system_item_import_request);
  if (!validator_->is_can_be_putted(system_item_list)) {
    log(logging::trivial::info, "invalid request");
    return response;
  }
  log(logging::trivial::debug, "request can be putted");

  if (!putter_->put(std::move(system_item_list))) {
    log(logging::trivial::info, "invalid request");
    return response;
  }
  log(logging::trivial::info, "request putted");

  response.status = valid_request;
  response.body = "";
  return response;
}

RouterResponse ImportsHandler::handle(RouterRequest &&request) {
  RouterResponse response;
  auto lg = my_logger::get();
  auto type = request.type;

  if (type == MessageType::post) {
    BOOST_LOG_SEV(lg, logging::trivial::debug) << "move to post handler";
    response = handle_message<MessageType::post>(std::move(request));
  } else {
    BOOST_LOG_SEV(lg, logging::trivial::warning) << "move to unknown handler";
  }

  return response;
}

ImportsHandler::ImportsHandler(std::shared_ptr<SystemItemImportRequestDSI> &&deserializer,
                               std::shared_ptr<SystemItemImportRequestVSI> &&raw_validator,
                               std::shared_ptr<ValidateNodeInterface> &&validator,
                               std::shared_ptr<PutNodeInterface> &&putter)
    : deserializer_(std::move(deserializer)),
      raw_validator_(std::move(raw_validator)),
      validator_(std::move(validator)),
      putter_(std::move(putter)) {}

ImportsHandler::ImportsHandler() : ImportsHandler(
    std::move(std::shared_ptr<SystemItemImportRequestDSI>{new SystemItemImportRequestDSJson()}),
    std::move(std::shared_ptr<SystemItemImportRequestVSI>{new SystemItemImportRequestVS()}),
    std::shared_ptr<ValidateNodeInterface>{new TreeValidator()},
    std::shared_ptr<PutNodeInterface>{Tree::get_instance()}
) {}
