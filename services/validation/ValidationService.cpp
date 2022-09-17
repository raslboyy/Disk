#include <boost/property_tree/ptree.hpp>
#include "ValidationService.h"
#include "../../tools/Time.h"

#include <sstream>

using PTree = boost::property_tree::ptree;

static bool validate_(const SystemItemImport &item) {
  if (item.id.empty())
    return false;
  if (item.type.empty())
    return false;
  if (item.type != "FILE" && item.type != "FOLDER")
    return false;
  return true;
}

static bool validate_(const SystemItem &item) {
  return true;
}

static bool validate_(const SystemItemImportRequest &item) {
  if (item.items.empty())
    return false;
  if (item.updateDate.empty())
    return false;

  auto iso8601 = false;
  parse_ISO8601(item.updateDate, iso8601);
  if (!iso8601)
    return false;

  if (std::any_of(item.items.begin(), item.items.end(),
                  [](const SystemItemImport &local_item) { return !validate_(local_item); }))
    return false;

  return true;
}

bool SystemItemImportRequestVS::validate(const SystemItemImportRequest &item) {
  return validate_(item);
}

bool SystemItemVS::validate(const SystemItem &item) {
  return validate_(item);
}
