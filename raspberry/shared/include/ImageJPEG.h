#ifndef IMAGE_JPEG_H
#define IMAGE_JPEG_H

#include <Image.h>

class ImageJPEG : public Image
{
  public:
    ImageJPEG();
    ~ImageJPEG();
    ImageJPEG(const Image* image);
};

#endif