
#include <CameraClient.h>
#include <debug.h>
#include <unistd.h>
#include <ClientHandler.h>
#include <Camera.h>
#include <Image.h>
#include <ImageJPEG.h>
#include <ImageRGB.h>
#include <string.h>
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
  debug(CAM_CLIENT, "run: Start\n");
  int     ret;
  Camera* camera = Camera::instance();
  Image*  image;

  struct ImageJsonData image_data;

  while (client_handler_->connected_)
  {
    camera->condLock();
    debug(CAM_CLIENT, "run: Sleep\n");
    camera->sleep();
    camera->lock();
    camera->condUnlock();
    image = camera->getImage();
    if (image != 0)
    {
      debug(CAM_CLIENT, "run: New picture\n");
      image->getMsg(&image_data);
      if (image_data.header_length_ > client_handler_->BUFFER_SIZE)
      {
        debug(ERROR, "CameraClient::run: image_data.header_length_ > client_handler_->BUFFER_SIZE\n");
        exit(-1);
      }
      memset(client_handler_->output_buffer_, 0, client_handler_->BUFFER_SIZE);
      memcpy(client_handler_->output_buffer_, image_data.header_, image_data.header_length_);
      if ((ret = client_handler_->transmit()) < 0)
      {
        debug(WARNING, "CameraClient::run: Transmittion failed\n");
        image->freeSpace(&image_data);
        camera->deleteImage();
        camera->unlock();
        break;
      }

      int   length = image_data.body_lenght_;
      char* buffer = image_data.body_;
      debug(CAM_CLIENT, "run: Start transmitting\n");
      while (length > 0)
      {
        if (length >= client_handler_->BUFFER_SIZE)
        {
          memcpy(client_handler_->output_buffer_, buffer, client_handler_->BUFFER_SIZE);
          buffer += client_handler_->BUFFER_SIZE;
          length -= client_handler_->BUFFER_SIZE;
        }
        else
        {
          debug(ERROR, "CameraClient::run: wrong\n");
          exit(-1);
        }

        if ((ret = client_handler_->transmit()) < 0)
        {
          break;
        }
      }
      debug(CAM_CLIENT, "run: End transmitting\n");
    }
    image->freeSpace(&image_data);
    camera->deleteImage();
    camera->unlock();
  }

  debug(CAM_CLIENT, "run: Exit\n");
}
