
#include <Image.h>
#include <string.h>
#include <debug.h>
#include <ImageJPEG.h>
#include <ImageRGB.h>
#if defined(__x86_64)
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#else // if defined(__arm__)
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#include <jsoncpp/json/value.h>
#endif

Image::Image(enum ImageType type) :
  lock_("Image::lock"),
  data_(0),
  size_(-1),
  width_(-1),
  height_(-1),
  type_(type)
{
  debug(IMAGE, "ctor: with type %d\n", type);
}

Image::~Image()
{
  debug(IMAGE, "dtor\n");
  delete data_;
}

int Image::set(unsigned int size, unsigned int width, unsigned int height)
{
  if (data_ != 0)
  {
    delete data_;
  }
  debug(IMAGE, "save: size <%d>, width <%d>, height <%d>\n", size, width, height);
  data_ = new unsigned char[size];
  size_ = size;
  width_ = width;
  height_ = height;
  return 0;
}