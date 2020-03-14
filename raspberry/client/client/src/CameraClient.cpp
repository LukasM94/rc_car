
#include <CameraClient.h>
#include <debug.h>
#include <unistd.h>
#include <ClientHandler.h>
#include <Camera.h>
#include <Image.h>
  
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
  debug(CAM_CLIENT, "run: Start\n");
  int     ret;
  Camera* camera = Camera::instance();
  Image*  image;

  struct Image::JsonData image_data;

  debug(CAM_CLIENT, "run: Start\n");

  while (client_handler_->connected_)
  {
    camera->condLock();
    camera->sleep();
    camera->lock();
    camera->condUnlock();
    image = camera->getImage();
    if (image != 0)
    {
      debug(CAM_CLIENT, "run: New picture\n");
      image->getMsg(&image_data);
    }
    camera->unlock();
  }

  debug(CAM_CLIENT, "run: Exit\n");
}
