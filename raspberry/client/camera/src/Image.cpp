
#include <Image.h>
#include <string.h>
#include <debug.h>


Image::Image(unsigned int size,
             unsigned int width,
             unsigned int height) :
  lock_("Image::lock"),
  data_(new unsigned char[size]),
  size_(size),
  width_(width),
  height_(height)
{
  debug(IMAGE, "ctor: size <%d>, width <%d>, height <%d>\n", size, width, height);
}

Image::Image(unsigned char* data, 
             unsigned int size,
             unsigned int width,
             unsigned int height) :
  lock_("Image::lock"),
  data_(new unsigned char[size]),
  size_(size),
  width_(width),
  height_(height)
{
  debug(IMAGE, "ctor: data <%p>, size <%d>, width <%d>, height <%d>\n", data, size, width, height);
  memcpy(data_, data, size_);
}

Image::~Image()
{
  debug(IMAGE, "dtor\n");
  delete data_;
}
