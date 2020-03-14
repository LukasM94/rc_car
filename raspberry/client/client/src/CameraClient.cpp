
#include <CameraClient.h>
#include <debug.h>
#include <unistd.h>
#include <ClientHandler.h>
#include <Camera.h>
#include <Image.h>
#include <ImageJPEG.h>
#include <ImageRGB.h>
  
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

      // TEST
      printf("data:\n");
      unsigned char* data = image->getData();
      for (int i = 0; i < image->getSize(); ++i)
      {
        printf("%c", data[i]);
      }
      printf("\n");
      // printf("header:\n");
      // printf("%s", image_data.header_);
      // printf("body:\n");
      // printf("%s", image_data.body_);

      // get header
      unsigned int size;
      Image::getSizeOfBody(image_data.header_, &size);
      debug(CAM_CLIENT, "run: Size of body is %d\n", size);

      // get body
      Image* jpeg = new ImageJPEG();
      Image::getFromString(jpeg, image_data.body_);
      printf("data:\n");
      data = jpeg->getData();
      for (int i = 0; i < jpeg->getSize(); ++i)
      {
        printf("%c", data[i]);
      }
      printf("\n");

      // get rgb image
      Image* rgb = new ImageRGB(jpeg);
      debug(CAM_CLIENT, "run: Got rgb back from %d to %d\n", jpeg->getSize(), rgb->getSize());

    }
    camera->unlock();
  }

  debug(CAM_CLIENT, "run: Exit\n");
}
