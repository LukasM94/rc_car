#ifndef IMAGE_JPEG_H
#define IMAGE_JPEG_H

#include <Image.h>

class ImageJPEG : public Image
{
  public:
    ImageJPEG();
    ~ImageJPEG();
    virtual int convertTo();
};

#endif