#ifndef IMAGE_H
#define IMAGE_H

#include <Lock.h>

enum ImageType
{
  RGB,
  JPEG,
};

class Image
{
  public:
    Image(enum ImageType);
    ~Image();
    int set(unsigned int size,
            unsigned int width,
            unsigned int height);
    virtual int convertTo() = 0;
    inline unsigned char* getData()
    {
      return data_;
    }
    inline unsigned int getSize()
    {
      return size_;
    }
    inline unsigned int getWidth()
    {
      return width_;
    }
    inline unsigned int getHeight()
    {
      return height_;
    }
    inline void lock()
    {
      lock_.lock();
    }
    inline void unlock()
    {
      lock_.unlock();
    }

  protected:
    Image();
    enum ImageType type_;
    
    Lock lock_;
    unsigned char* data_;
    unsigned int size_;
    unsigned int width_;
    unsigned int height_;
};

#endif