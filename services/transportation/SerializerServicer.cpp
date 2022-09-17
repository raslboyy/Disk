#include "SerializerServicer.h"

std::string SystemItemImportResponseSSJson::serialize(const SystemItemExport &response) {
  return boost::json::serialize(boost::json::value_from(response));
}
