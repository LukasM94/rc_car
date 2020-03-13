
#include <ImageJPEG.h>
#include <debug.h>

ImageJPEG::ImageJPEG() :
  Image(JPEG)
{
  debug(IMAGE_JPEG, "ctor\n");
}

ImageJPEG::~ImageJPEG()
{
  debug(IMAGE_JPEG, "dtor\n");
}

int ImageJPEG::convertTo()
{
  debug(IMAGE_JPEG, "convertTo\n");
  return -1;
}