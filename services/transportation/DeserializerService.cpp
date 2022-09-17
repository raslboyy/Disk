#include "DeserializerService.h"

SystemItemImportRequest SystemItemImportRequestDSJson::deserialize(std::string text) {
  JsonValue jv = boost::json::parse(text);
  return boost::json::value_to<SystemItemImportRequest>(jv);
}