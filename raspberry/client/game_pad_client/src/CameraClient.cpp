
#include <sched.h>
#include <algorithm> 
#include <CameraClient.h>
#include <debug.h>
#include <ClientHandler.h>
  
//-------------------------------------------------
CameraClient::CameraClient(ClientHandler* client_handler) :
  WorkingThread("CameraClient"),
  client_handler_(client_handler)
{
  debug(CAM_CLIENT, "ctor: %p\n", client_handler);
}

//-------------------------------------------------
CameraClient::~CameraClient()
{
  debug(CAM_CLIENT, "dtor:\n");
}

//-------------------------------------------------
void CameraClient::run()
{
  int ret = 0;

  debug(CAM_CLIENT, "run: Start\n");

  while (client_handler_->connected_)
  {
    sched_yield();
  }

  debug(CAM_CLIENT, "run: Exit\n");
}
