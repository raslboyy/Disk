#ifndef DISK_SERVICES_TREE_API_DELETENODEINTERFACE_H_
#define DISK_SERVICES_TREE_API_DELETENODEINTERFACE_H_

#include <string>

struct DeleteNodeInterface {
  virtual bool delete_(std::string_view id, std::string_view date) = 0;
};

#endif //DISK_SERVICES_TREE_API_DELETENODEINTERFACE_H_
