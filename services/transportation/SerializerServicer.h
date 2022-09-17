#ifndef DISK_SERVICES_TRANSPORTATION_SERIALIZERSERVICER_H_
#define DISK_SERVICES_TRANSPORTATION_SERIALIZERSERVICER_H_

#include "SerializerServiceInterface.h"

class SystemItemImportResponseSSJson : public SystemItemImportResponseSSI {
 public:
  std::string serialize(const SystemItemExport &response) override;
};

#endif //DISK_SERVICES_TRANSPORTATION_SERIALIZERSERVICER_H_
