
#include <ImageInstance.h>
#include <Image.h>
#include <ImageRGB.h>
#include <debug.h>
#include <ServerHandler.h>

ImageInstance* ImageInstance::instance_ = 0;

ImageInstance::ImageInstance() :
  image_(0),
  cond_("ImageInstance")
{
  debug(IMAGE_INSTA, "ctor\n");
}

ImageInstance::~ImageInstance()
{
  if (image_ != 0)
  {
    delete image_;
  }
  debug(IMAGE_INSTA, "ctor\n");
}

ImageInstance* ImageInstance::instance()
{
  if (instance_ == 0)
  {
    instance_ = new ImageInstance();
  }
  return instance_;
}

int ImageInstance::saveImage(Image* image)
{
  debug(IMAGE_INSTA, "saveImage: image <%p>\n", image);
  cond_.lock();
  if (image_ != 0)
  {
    delete image_;
    image_ = 0;
  }
  image_ = new ImageRGB(image);
  cond_.wake();
  cond_.unlock();
  return 0;
}

Image* ImageInstance::loadImage(bool sleep)
{
  debug(IMAGE_INSTA, "loadImage\n");
  Image* image;
  cond_.lock();
  while (image_ == 0)
  {
    ServerHandler* server_handler = ServerHandler::instance();
    if (server_handler->isConnected() == false)
    {
      cond_.unlock();
      return 0;
    }

    if (sleep)
    {
      cond_.sleep(1000);
    }
    else
    {
      cond_.unlock();
      return 0;
    }
  }
  image = new ImageRGB(image_);
  debug(IMAGE_INSTA, "loadImage: image <%p>\n", image);
  delete image_;
  image_ = 0;
  cond_.unlock();
  return image;
}

void ImageInstance::freeImage(Image* image)
{
  debug(IMAGE_INSTA, "freeImage: image <%p>\n", image);
  delete image;
}
