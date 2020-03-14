
#include <Image.h>
#include <string.h>
#include <debug.h>
#include <ImageJPEG.h>
#include <ImageRGB.h>
#include <string>
#include <unistd.h>
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
  debug(IMAGE, "ctor: Type <%d>\n", type);
}

Image::Image(const Image* image, enum ImageType type) :
  lock_("Image::lock"),
  data_(0),
  size_(-1),
  width_(image->width_),
  height_(image->height_),
  type_(type)
{
  debug(IMAGE, "ctor: Width <%d>, height <%d>, type <%d>\n", width_, height_, type_);
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

int Image::getHeader(char** header_str, int size)
{
  debug(IMAGE, "getHeader: Start\n");
  debug(IMAGE, "getHeader: Size of body is %d\n", size);
  unsigned int length = -1;

  try
  {
    Json::Value header;

    header[0] = STRING_HEADER;
    header[1] = size;

    length = header.toStyledString().length();
    if (length > PACKAGE_LENGTH)
    {
      return 2;
    }
    
    *header_str = new char[PACKAGE_LENGTH];
    memset(*header_str, 0, PACKAGE_LENGTH);
    memcpy(*header_str, header.toStyledString().c_str(), length);
  }
  catch (Json::Exception& e)
  {
    debug(WARNING, "Image::getHeader: %s\n", e.what());
    return 1;
  }

  debug(IMAGE, "getHeader: Finished with header length of %d\n", length);
  return 0;
}

int Image::getBody(char** body_str, int* size)
{
  debug(IMAGE, "getBody: Start\n");

  try
  {
    Json::Value body;
    Json::Value data;

    data[STRING_SIZE]   = size_;
    data[STRING_WIDTH]  = width_;
    data[STRING_HEIGHT] = height_;
    data[STRING_DATA]   = Json::Value((const char*)data_, (const char*)(data_ + size_));

    body[0] = STRING_BODY;
    body[1] = data;

    *size = body.toStyledString().length();
    *size = ((((*size) / PACKAGE_LENGTH) + 1) * PACKAGE_LENGTH);

    *body_str = new char[*size];
    memset(*body_str, 0, *size);
    memcpy(*body_str, body.toStyledString().c_str(), body.toStyledString().length());
  }
  catch (Json::Exception& e)
  {
    debug(WARNING, "Image::getBody: %s\n", e.what());
    return 4;
  }

  debug(IMAGE, "getBody: Finished with length of %d\n", *size);
  return 0;
}

int Image::getMsg(struct ImageJsonData* data)
{
  debug(IMAGE, "getMsg: data <%p>\n", data);
  int ret;
  data->header_length_ = PACKAGE_LENGTH;
  if ((ret = (getBody(&data->body_, &data->body_lenght_) ||
              getHeader(&data->header_, data->body_lenght_))) != 0)
  {
    return ret;
  }

  return 0;
}

int Image::freeSpace(struct ImageJsonData* data)
{
  debug(IMAGE, "freeSpace: data <%p>\n", data);
  delete data->body_;
  delete data->header_;
  return 0;
}

int Image::getSizeOfBody(const char* header_str, int* size)
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
    *size = data.asUInt();
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
  try
  {
    Json::Reader reader;
    Json::Value  body;
    Json::Value  data;

    // debug(IMAGE, "getFromString: Start parse\n");
    int ret = reader.parse(body_str, body);
    if (ret == 0)
    {
      debug(WARNING, "Image::getSizeOfBody: parsing not successful\n");
      return 1;
    }

    // debug(IMAGE, "getFromString: Get body value\n");
    std::string body_value = body[0].asString();
    if (body_value.compare(STRING_BODY) != 0)
    {
      debug(WARNING, "Image::getSizeOfBody: parsing not successful\n");
      return 2;
    }

    data = body[1];

    // debug(IMAGE, "getFromString: Get width\n");
    image->width_  = data[STRING_WIDTH].asUInt();
    // debug(IMAGE, "getFromString: Get size\n");
    image->size_   = data[STRING_SIZE].asUInt();
    // debug(IMAGE, "getFromString: Get height\n");
    image->height_ = data[STRING_HEIGHT].asUInt();
    // debug(IMAGE, "getFromString: Get data\n");
    image->data_ = new unsigned char[image->size_];
    memcpy(image->data_, (unsigned char*)data[STRING_DATA].asCString(), image->size_);
  }
  catch (Json::Exception& e)
  {
    debug(WARNING, "Image::getFromString: %s\n", e.what());
    return -1;
  }

  return -1;
}

void Image::print()
{
  debug(WARNING, "Image::print: Not possible for Image!!!!\n");
}