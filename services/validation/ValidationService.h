#ifndef DISK_SERVICES_VALIDATIONSERVICE_H_
#define DISK_SERVICES_VALIDATIONSERVICE_H_

#include "ValidationServiceInterface.h"
#include "../../entities/transport/SystemItemImportRequest.h"
#include "../../entities/model/SystemItem.h"

class SystemItemImportRequestVS : public SystemItemImportRequestVSI {
 public:
  bool validate(const SystemItemImportRequest &item) override;
};

class SystemItemVS : public SystemItemVSI {
 public:
  bool validate(const SystemItem &item) override;
};

#endif //DISK_SERVICES_VALIDATIONSERVICE_H_