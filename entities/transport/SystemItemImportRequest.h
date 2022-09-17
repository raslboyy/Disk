#ifndef DISK_ENTITIES_TRANSPORT_SYSTEMITEMIMPORTREQUEST_H_
#define DISK_ENTITIES_TRANSPORT_SYSTEMITEMIMPORTREQUEST_H_

#include <vector>

#include "SystemItemImport.h"
#include "../../tools/json.h"

struct SystemItemImportRequest {
  std::vector<SystemItemImport> items;
  std::string updateDate;
};

template<class T>
static void extract(Json const &obj, T &t, std::string key);

SystemItemImportRequest tag_invoke(boost::json::value_to_tag<SystemItemImportRequest>, JsonValue const &jv);

#endif //DISK_ENTITIES_TRANSPORT_SYSTEMITEMIMPORTREQUEST_H_
