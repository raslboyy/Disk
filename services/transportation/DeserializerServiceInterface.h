#ifndef DISK_SERVICES_TRANSPORTATION_DESERIALIZERSERVICEINTERFACE_H_
#define DISK_SERVICES_TRANSPORTATION_DESERIALIZERSERVICEINTERFACE_H_

#include "../../entities/transport/SystemItemImportRequest.h"

class SystemItemImportRequestDSI {
 public:
  virtual SystemItemImportRequest deserialize(std::string text) = 0;
};

#endif //DISK_SERVICES_TRANSPORTATION_DESERIALIZERSERVICEINTERFACE_H_
