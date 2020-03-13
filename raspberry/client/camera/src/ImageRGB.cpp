
#include <ImageRGB.h>
#include <debug.h>

ImageRGB::ImageRGB() :
  Image(RGB)
{
  debug(IMAGE_RGB, "ctor\n");
}

ImageRGB::~ImageRGB()
{
  debug(IMAGE_RGB, "dtor\n");
}

int ImageRGB::convertTo()
{
  debug(IMAGE_RGB, "convertTo\n");
  return -1;
}