
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
      client_handler_->transmit();

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

        int ret;
        if ((ret = client_handler_->transmit()) < 0)
        {
          break;
        }
      }
      debug(CAM_CLIENT, "run: End transmitting\n");

      // TEST
      // printf("data:\n");
      // unsigned char* data = image->getData();
      // for (int i = 0; i < image->getSize(); ++i)
      // {
      //   printf("%d, ", data[i]);
      // }
      // printf("\n");
      // printf("header:\n");
      // printf("%s", image_data.header_);
      // printf("body:\n");
      // printf("%s", image_data.body_);

      // get header
      // unsigned int size;
      // Image::getSizeOfBody(image_data.header_, &size);
      // debug(CAM_CLIENT, "run: Size of body is %d\n", size);

      // get body
      // Image* jpeg = new ImageJPEG();
      // Image::getFromString(jpeg, image_data.body_);
      // printf("data:\n");
      // data = jpeg->getData();
      // for (int i = 0; i < jpeg->getSize(); ++i)
      // {
      //   printf("%d, ", data[i]);
      // }
      // printf("\n");

      // get rgb image
      // Image* rgb = new ImageRGB(image);
      // Image* rgb = new ImageRGB(jpeg);
      // debug(CAM_CLIENT, "run: Got rgb back from %d to %d\n", jpeg->getSize(), rgb->getSize());
      // rgb->print();
    }
    camera->unlock();
  }

  debug(CAM_CLIENT, "run: Exit\n");
}
