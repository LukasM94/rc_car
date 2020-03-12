#ifndef IMAGE_H
#define IMAGE_H

#include <Lock.h>

class Image
{
  public:
    Image(unsigned int size,
          unsigned int width,
          unsigned int height);
    Image(unsigned char* data, 
          unsigned int size,
          unsigned int width,
          unsigned int height);
    ~Image();
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

    private:
      Image();
      
      Lock lock_;
      unsigned char* data_;
      unsigned int size_;
      unsigned int width_;
      unsigned int height_;
};

#endif