
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

const char Image::STRING_HEADER[] = "header";
const char Image::STRING_BODY[]   = "body";
const char Image::STRING_DATA[]   = "data";
const char Image::STRING_SIZE[]   = "size";
const char Image::STRING_WIDTH[]  = "w";
const char Image::STRING_HEIGHT[] = "h";

int Image::getHeader(char** header_str, unsigned int size)
{
  debug(IMAGE, "getHeader: Start\n");
  Json::Value header;

  try
  {
    header[0] = STRING_HEADER;
    header[1] = size;
  }
  catch (Json::Exception& e)
  {
    debug(WARNING, "Image::getHeader: %s\n", e.what());
    return 1;
  }

  unsigned int length = header.toStyledString().length();
  if (length > PACKAGE_LENGTH)
  {
    return 2;
  }

  *header_str = new char[length];
  memset(*header_str, 0, PACKAGE_LENGTH);
  memcpy(*header_str, header.toStyledString().c_str(), length);
  debug(IMAGE, "getHeader: Finished with length of %d\n", length);
  return 0;
}

int Image::getBody(char** body_str, unsigned int* size)
{
  debug(IMAGE, "getHeader: Start\n");
  Json::Value body;
  Json::Value data((const char*)data_, (const char*)(data_ + size_));

  try
  {
    body[0] = STRING_HEADER;
    body[1] = width_;
    body[2] = height_;
    body[3] = size_;
    body[4] = data;
  }
  catch (Json::Exception& e)
  {
    debug(WARNING, "Image::getBody: %s\n", e.what());
    return 4;
  }

  *size = body.toStyledString().length();
  *size = ((((*size) / PACKAGE_LENGTH) + 1) * PACKAGE_LENGTH);

  *body_str = new char[*size];
  memset(*body_str, 0, *size);
  memcpy(*body_str, body.toStyledString().c_str(), body.toStyledString().length());

  debug(IMAGE, "getBody: Finished with length of %d\n", *size);
  return 0;
}

int Image::getMsg(struct JsonData* data)
{
  debug(IMAGE, "getMsg: data <%p>\n", data);
  int ret;
  lock();
  data->header_length_ = PACKAGE_LENGTH;
  if ((ret = (getBody(&data->body_, &data->body_lenght_) ||
              getHeader(&data->header_, data->body_lenght_))) != 0)
  {
    unlock();
    return ret;
  }
  unlock();

  return 0;
}

int Image::freeSpace(struct JsonData* data)
{
  debug(IMAGE, "freeSpace: data <%p>\n", data);
  delete data->body_;
  delete data->header_;
  return 0;
}

int Image::getSizeOfBody(const char* header_str, unsigned int* size)
{
  Json::Reader reader;
  Json::Value  header;
  Json::Value  data;

  try
  {
    int ret = reader.parse(header_str, header);
    if (ret == 0)
    {
      debug(WARNING, "Image::getSizeOfBody: parsing not successful\n");
      return 1;
    }

    std::string header_value = header[0].asString();
    if (header_value.compare(STRING_HEADER) != 0)
    {
      debug(WARNING, "Image::getSizeOfBody: parsing not successful\n");
      return 2;
    }

    data = header[1].asUInt();
  }
  catch (Json::Exception& e)
  {
    debug(WARNING, "Image::getSizeOfBody: %s\n", e.what());
    return 4;
  }
  return 0;
}

int Image::getFromString(Image* image, const char* body_str)
{
  Json::Reader reader;
  Json::Value  body;
  Json::Value  data;

  try
  {
    int ret = reader.parse(body_str, body);
    if (ret == 0)
    {
      debug(WARNING, "Image::getSizeOfBody: parsing not successful\n");
      return 8;
    }
  }
  catch (Json::Exception& e)
  {
    debug(WARNING, "Image::getFromString: %s\n", e.what());
    return -1;
  }

  return -1;
}

