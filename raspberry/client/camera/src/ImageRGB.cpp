
#include <ImageRGB.h>
#include <debug.h>
#include <jpeglib.h>
#include <string.h>

ImageRGB::ImageRGB() :
  Image(RGB)
{
  debug(IMAGE_RGB, "ctor\n");
}

ImageRGB::~ImageRGB()
{
  debug(IMAGE_RGB, "dtor\n");
}

ImageRGB::ImageRGB(const Image* image) : 
  Image(RGB)
{
  debug(IMAGE_RGB, "ImageRGB(const Image* image)\n");
  int ret;
  int row_stride;

  unsigned char* data = image->getData();
  unsigned long  size = image->getSize();

  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;

  JSAMPROW row_pointer[1];

  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_decompress(&cinfo);

  jpeg_mem_src(&cinfo, data, size);

  ret = jpeg_read_header(&cinfo, TRUE);
  if (ret != 1)
  {
    debug(WARNING, "ImageRGB::ImageRGB(const Image* image): Seems not to be a normal jpeg\n");
    return;
  }

  jpeg_start_decompress(&cinfo);
  width_  = cinfo.output_width;
  height_ = cinfo.output_height;
  size_   = width_ * height_ * cinfo.output_components;
  data_   = new unsigned char[size_];

  row_stride = width_ * cinfo.output_components;

  debug(IMAGE_RGB, "ImageRGB(const Image* image): Start decompressing\n");

  while (cinfo.output_scanline < cinfo.output_height)
  {
    unsigned char *buffer_array[1];
    buffer_array[0] = data_ + (cinfo.output_scanline) * row_stride;
    jpeg_read_scanlines(&cinfo, buffer_array, 1);
  }
  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
  debug(IMAGE_RGB, "ImageRGB(const Image* image): Finished decompressing\n");
}
