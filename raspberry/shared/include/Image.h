#ifndef IMAGE_H
#define IMAGE_H

#include <Lock.h>

enum ImageType
{
  RGB,
  JPEG,
};

namespace Json
{
  class Value;
}

class Image
{
  public:
    Image(enum ImageType);
    ~Image();

    struct JsonData
    {
      char*        header_;
      unsigned int header_length_;
      char*        body_;
      unsigned int body_lenght_;
    };

    static int getFromString(Image* image, const char* body);
    static int getSizeOfBody(const char* header, unsigned int* size);
    int getMsg(struct JsonData* data);
    int freeSpace(struct JsonData* data);

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

    static const unsigned int PACKAGE_LENGTH = 256;

  protected:
    Image();
    
    int getHeader(char** header, unsigned int size);
    int getBody(char** body, unsigned int* size);

    enum ImageType type_;
    
    Lock lock_;
    unsigned char* data_;
    unsigned int   size_;
    unsigned int   width_;
    unsigned int   height_;

    char* msg_;

    static const char STRING_HEADER[];
    static const char STRING_BODY[];
    static const char STRING_DATA[];
    static const char STRING_SIZE[];
    static const char STRING_WIDTH[];
    static const char STRING_HEIGHT[];
};

#endif