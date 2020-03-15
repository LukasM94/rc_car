
#include <ImageInstance.h>
#include <Image.h>
#include <debug.h>

ImageInstance* ImageInstance::instance_ = 0;

ImageInstance::ImageInstance() :
  image_(0)
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

int ImageInstance::setImage(Image* image)
{
  debug(IMAGE_INSTA, "setImage: image <%p>\n", image);
  if (image->getType() != ImageType::RGB)
  {
    debug(WARNING, "ImageInstance::setImage: image <%p> is not rgb\n", image);
    return -1;
  }
  if (image_ != 0)
  {
    delete image_;
  } 
  image_ = image;
  return 0;
}
