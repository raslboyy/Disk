#ifndef DISK_API_CONTROLLER_IMPORTSHANDLER_H_
#define DISK_API_CONTROLLER_IMPORTSHANDLER_H_

#include "HandlerInterface.h"
#include "../../services/validation/ValidationService.h"
#include "../../entities/transport/SystemItemImportRequest.h"
#include "../../services/transportation/DeserializerServiceInterface.h"
#include "../../services/storage/api/PutNodeInterface.h"
#include "../../services/storage/api/ValidateNodeInterface.h"

class ImportsHandler : public HandlerInterface {
  std::shared_ptr<SystemItemImportRequestDSI> deserializer_;
  std::shared_ptr<SystemItemImportRequestVSI> raw_validator_;
  std::shared_ptr<ValidateNodeInterface> validator_;
  std::shared_ptr<PutNodeInterface> putter_;

  template<MessageType type>
  RouterResponse handle_message(RouterRequest &&request);
 public:
  ImportsHandler();
  ImportsHandler(std::shared_ptr<SystemItemImportRequestDSI> &&deserializer,
                 std::shared_ptr<SystemItemImportRequestVSI> &&raw_validator,
                 std::shared_ptr<ValidateNodeInterface> &&validator,
                 std::shared_ptr<PutNodeInterface> &&putter);
  RouterResponse handle(RouterRequest &&request) override;
};

#endif //DISK_API_CONTROLLER_IMPORTSHANDLER_H_
