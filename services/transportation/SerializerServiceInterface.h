#ifndef DISK_SERVICES_TRANSPORTATION_SERIALIZERSERVICEINTERFACE_H_
#define DISK_SERVICES_TRANSPORTATION_SERIALIZERSERVICEINTERFACE_H_

#include "../../entities/transport/SystemItemExport.h"

class SystemItemImportResponseSSI {
 public:
  virtual std::string serialize(const SystemItemExport &response) = 0;
};

#endif //DISK_SERVICES_TRANSPORTATION_SERIALIZERSERVICEINTERFACE_H_