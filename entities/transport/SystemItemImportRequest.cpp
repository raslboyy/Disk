#include "SystemItemImportRequest.h"

SystemItemImportRequest tag_invoke(boost::json::value_to_tag<SystemItemImportRequest>, JsonValue const &jv) {
  SystemItemImportRequest c;
  Json const &obj = jv.as_object();
  extract(obj, c.items, "items");
  extract(obj, c.updateDate, "updateDate");
  return c;
}
template<class T>
void extract(const Json &obj, T &t, std::string key) {
  if (obj.contains(key) && !obj.at(key).is_null())
    t = boost::json::value_to<T>(obj.at(key));
}