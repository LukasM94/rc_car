
#include <debug.h>
#include <ImageJPEG.h>
#include <jpeglib.h>
#include <string.h>

ImageJPEG::ImageJPEG() :
  Image(JPEG)
{
  debug(IMAGE_JPEG, "ctor\n");
}

ImageJPEG::~ImageJPEG()
{
  debug(IMAGE_JPEG, "dtor\n");
}

ImageJPEG::ImageJPEG(const Image* image) :
  Image(image, JPEG)
{
  debug(IMAGE_JPEG, "ImageJPEG(const Image* image)\n");
  unsigned char* data = image->getData();

  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;

  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);
  unsigned long size;
  jpeg_mem_dest(&cinfo, &data_, &size);
  size_ = (unsigned int)size;

  cinfo.image_width = image->getWidth();  
  cinfo.image_height = image->getHeight();
  cinfo.input_components = image->getSize() / (image->getWidth() * image->getHeight());
  cinfo.in_color_space   = JCS_RGB;
  jpeg_set_defaults(&cinfo);

  debug(IMAGE_JPEG, "ImageJPEG(const Image* image): Start compression\n");
  jpeg_set_quality (&cinfo, 75, true);
  jpeg_start_compress(&cinfo, TRUE);
  while (cinfo.next_scanline < cinfo.image_height)
  {
    JSAMPROW row_pointer[1];
    row_pointer[0] = &data[cinfo.next_scanline * cinfo.image_width * cinfo.input_components];
    jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }

  debug(IMAGE_JPEG, "ImageJPEG(const Image* image): Finish compression\n");
  jpeg_finish_compress(&cinfo);
  jpeg_destroy_compress(&cinfo);

  debug(IMAGE_JPEG, "ImageJPEG(const Image* image): Finished\n");
}

void ImageJPEG::print()
{
  debug(WARNING, "ImageJPEG::print: Not possible for now\n");
}