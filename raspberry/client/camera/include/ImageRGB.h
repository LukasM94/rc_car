#ifndef IMAGE_RGB_H
#define IMAGE_RGB_H

#include <Image.h>

class ImageRGB : public Image
{
  public:
    ImageRGB();
    ~ImageRGB();
    virtual int convertTo();
};

#endif