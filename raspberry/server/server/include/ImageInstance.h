#ifndef IMAGE_INSTANCE_H
#define IMAGE_INSTANCE_H

#include <Cond.h>

class Image;

class ImageInstance
{
  public:
    ~ImageInstance();
    static ImageInstance* instance();

    int    saveImage(Image* image);
    Image* loadImage();
    void   freeImage(Image* image);

  private:
    ImageInstance();
    static ImageInstance* instance_;

    Image* image_;
    Cond   cond_;
};

#endif