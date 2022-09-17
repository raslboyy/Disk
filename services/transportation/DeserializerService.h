#ifndef DISK_SERVICES_TRANSPORTATION_DESERIALIZERSERVICE_H_
#define DISK_SERVICES_TRANSPORTATION_DESERIALIZERSERVICE_H_

#include "DeserializerServiceInterface.h"

class SystemItemImportRequestDSJson : public SystemItemImportRequestDSI {
 public:
  SystemItemImportRequest deserialize(std::string text) override;
};

#endif //DISK_SERVICES_TRANSPORTATION_DESERIALIZERSERVICE_H_
