#ifndef DISK_SERVICES_VALIDATION_VALIDATIONSERVICEINTERFACE_H_
#define DISK_SERVICES_VALIDATION_VALIDATIONSERVICEINTERFACE_H_

#include "../../entities/transport/SystemItemImportRequest.h"
#include "../../entities/model/SystemItem.h"

class SystemItemImportRequestVSI {
 public:
  virtual bool validate(const SystemItemImportRequest &item) = 0;
};

class SystemItemVSI {
 public:
  virtual bool validate(const SystemItem &item) = 0;
};

#endif //DISK_SERVICES_VALIDATION_VALIDATIONSERVICEINTERFACE_H_
