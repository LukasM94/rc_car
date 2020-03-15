
#include <ImageInstance.h>
#include <Image.h>
#include <ImageRGB.h>
#include <debug.h>

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
  image_->print();
  cond_.wake();
  cond_.unlock();
  return 0;
}

Image* ImageInstance::loadImage()
{
  debug(IMAGE_INSTA, "loadImage\n");
  Image* image;
  cond_.lock();
  while (image_ == 0)
  {
    cond_.sleep();
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
