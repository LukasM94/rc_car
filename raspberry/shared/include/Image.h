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

    static int getFromString(Image* image, const char* str);
    int getMsg(const char** msg, unsigned long* size);
    int freeSpace();

    int set(unsigned int size,
            unsigned int width,
            unsigned int height);
    inline unsigned char* getData() const
    {
      return data_;
    }
    inline unsigned long getSize() const
    {
      return size_;
    }
    inline unsigned int getWidth() const  
    {
      return width_;
    }
    inline unsigned int getHeight() const
    {
      return height_;
    }
    inline enum ImageType getType() const
    {
      return type_;
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
    unsigned long  size_;
    unsigned int   width_;
    unsigned int   height_;

    char* msg_;
};

#endif