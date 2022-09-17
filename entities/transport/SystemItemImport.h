#ifndef DISK_ENTITIES_SYSTEMITEMIMPORT_H_
#define DISK_ENTITIES_SYSTEMITEMIMPORT_H_

#include <string>
#include "../../tools/json.h"

struct SystemItemImport {
  std::string id;
  std::string url;
  std::string parentId;
  std::string type;
  int64_t size = 0;
};

template<class T>
static void extract(Json const &obj, T &t, std::string key);

SystemItemImport tag_invoke(boost::json::value_to_tag<SystemItemImport>, JsonValue const &jv);

#endif //DISK_ENTITIES_SYSTEMITEMIMPORT_H_
