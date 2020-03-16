#ifndef IMAGE_RGB_H
#define IMAGE_RGB_H

#include <jpeglib.h>
#include <Image.h>

class ImageRGB : public Image
{
  public:
    ImageRGB();
    ~ImageRGB();
    ImageRGB(const Image* image);
    virtual void print();
    void printRaw();
};

#endif