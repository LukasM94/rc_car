#ifndef IMAGE_INSTANCE_H
#define IMAGE_INSTANCE_H

class Image;

class ImageInstance
{
  public:
    ~ImageInstance();
    static ImageInstance* instance();
    int setImage(Image* image);
  private:
    ImageInstance();
    static ImageInstance* instance_;

    Image* image_;
};

#endif