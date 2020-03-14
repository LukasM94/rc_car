
#include <CameraService.h>
#include <debug.h>
#include <Image.h>
#include <ServerHandler.h>

CameraService::CameraService(ServerHandler* server_handler) :
  WorkingThread("CameraService"),
  server_handler_(server_handler),
  image_(0)
{
  debug(CAM_SERVICE, "ctor: service_handler <%p>\n", server_handler_);
}

CameraService::~CameraService()
{
  debug(CAM_SERVICE, "dtor\n");
}

void CameraService::run()
{
  debug(CAM_SERVICE, "run: Start\n");
  while (server_handler_->connected_)
  {
    server_handler_->receive();
    debug(CAM_SERVICE, "run: Got message\n");
  }
  debug(CAM_SERVICE, "run: Exit\n");
}