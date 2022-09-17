#ifndef DISK_API_CONTROLLER_NODESHANDLER_H_
#define DISK_API_CONTROLLER_NODESHANDLER_H_

#include "HandlerInterface.h"
#include "../../services/transportation/SerializerServiceInterface.h"
#include "../../services/storage/api/GetNodeInterface.h"

class NodesHandler : public HandlerInterface {
  std::shared_ptr<SystemItemImportResponseSSI> serializer_;
  std::shared_ptr<GetNodeInterface> getter_;
  template<MessageType type>
  RouterResponse handle_message(RouterRequest &&request);
 public:
  NodesHandler();
  NodesHandler(std::shared_ptr<SystemItemImportResponseSSI> &&serializer,
               std::shared_ptr<GetNodeInterface> &&getter);
  RouterResponse handle(RouterRequest &&request) override;
};

#endif //DISK_API_CONTROLLER_NODESHANDLER_H_
