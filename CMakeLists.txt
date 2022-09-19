cmake_minimum_required(VERSION 3.22)
project(Disk)

set(CMAKE_CXX_STANDARD 23)
SET(CMAKE_CXX_FLAGS -pthread)

SET(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
FIND_PACKAGE(Boost
        1.80
        COMPONENTS log_setup log json
        REQUIRED)
include_directories(Boost::log Boost::json)

add_executable(Disk main.cpp http/core/beast.h http/core/net.h http/core/Listener.cpp http/core/Listener.h http/core/Http_session.cpp http/core/Http_session.h tools/Logger.cpp tools/Logger.h http/core/Server.h http/api/Router.cpp http/api/Router.h http/core/Server.cpp http/api/ImportsHandler.cpp http/api/ImportsHandler.h http/api/HandlerInterface.h http/api/DeleteHandler.cpp http/api/DeleteHandler.h http/api/NodesHandler.cpp http/api/NodesHandler.h tools/json.h services/validation/ValidationService.cpp services/validation/ValidationService.h entities/transport/SystemItemImport.h entities/transport/SystemItemImportRequest.h entities/transport/SystemItemImport.cpp entities/transport/SystemItemImportRequest.cpp services/validation/ValidationServiceInterface.h entities/model/SystemItem.cpp entities/model/SystemItem.h entities/model/SystemItemType.h services/transportation/DeserializerServiceInterface.h services/transportation/DeserializerService.cpp services/transportation/DeserializerService.h tools/Time.h tools/Time.cpp entities/model/SystemItemList.cpp entities/model/SystemItemList.h entities/transport/SystemItemExport.cpp entities/transport/SystemItemExport.h services/transportation/SerializerServiceInterface.h services/transportation/SerializerServicer.cpp services/transportation/SerializerServicer.h services/storage/api/GetNodeInterface.h services/storage/api/PutNodeInterface.h services/storage/api/DeleteNodeInterface.h services/storage/api/ValidateNodeInterface.h services/storage/core/Tree.cpp services/storage/core/Tree.h services/storage/core/Node.cpp services/storage/core/Node.h services/storage/validation/TreeValidator.cpp services/storage/validation/TreeValidator.h tools/Config.h tools/Config.cpp)
target_link_libraries(Disk Boost::log Boost::json)