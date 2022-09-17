#include "SystemItemImport.h"

SystemItemImport tag_invoke(boost::json::value_to_tag<SystemItemImport>, JsonValue const &jv) {
  SystemItemImport c;
  Json const &obj = jv.as_object();
  extract(obj, c.id, "id");
  extract(obj, c.url, "url");
  extract(obj, c.parentId, "parentId");
  extract(obj, c.type, "type");
  extract(obj, c.size, "size");
  return c;
}
template<class T>
void extract(const Json &obj, T &t, std::string key) {
  if (obj.contains(std::string{key}) && !obj.at(std::string{key}).is_null())
    t = boost::json::value_to<T>(obj.at(std::string{key}));
}
