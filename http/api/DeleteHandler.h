#ifndef DISK_API_CONTROLLER_DELETEHANDLER_H_
#define DISK_API_CONTROLLER_DELETEHANDLER_H_

#include <memory>

#include "HandlerInterface.h"
#include "../../services/storage/api/DeleteNodeInterface.h"

class DeleteHandler : public HandlerInterface {
  std::shared_ptr<DeleteNodeInterface> eraser_;
  template<MessageType type>
  RouterResponse handle_message(RouterRequest &&request);
 public:
  DeleteHandler();
  explicit DeleteHandler(std::shared_ptr<DeleteNodeInterface> &&eraser);
  RouterResponse handle(RouterRequest &&request) override;
};

#endif //DISK_API_CONTROLLER_DELETEHANDLER_H_
