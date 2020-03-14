#include <debug.h>
#include <CameraHandler.h>
#include <string.h>
#include <Image.h>
#include <ImageJPEG.h>
#include <ImageRGB.h>
#include <fstream>
#include <unistd.h>
#if defined(__arm__)
#include <raspicam/raspicam.h>
#endif

CameraHandler::CameraHandler() :
  WorkingThread("CameraHandler"),
  image_(0),
  raspi_cam_(0),
  lock_("CameraHandler::lock_")
{
  debug(CAMERA, "ctor\n");
}

CameraHandler::~CameraHandler()
{
#if defined(__arm__)
  if (raspi_cam_ != 0)
  {
    delete raspi_cam_;
  }
#endif
  debug(CAMERA, "dtor\n");
}

void CameraHandler::run()
{
  init();
  debug(CAMERA, "run: Start\n");
  while (running_)
  {
    debug(CAMERA, "run: Sleep 1 second\n");
    sleep(1);

    int ret;
    lock();
    if ((ret = grab()) != 0)
    {
      debug(WARNING, "camera_handler::run: grab returned %d\n", ret);
    }
    debug(CAMERA, "run: Took picture\n");
#if defined(__print_image)
    image_->lock();
#endif
    unlock();
#if defined(__print_image)
    ImageJPEG* jpeg = (ImageJPEG*)image_;
    image_          = new ImageRGB(image_);
    debug(CAMERA, "grab: Got the rgb back %d to %d\n", jpeg->getSize(), image_->getSize());
    delete jpeg;
    std::ofstream outFile ("raspicam_image.ppm",std::ios::binary);
	  outFile << "P6\n" << image_->getWidth() <<" "<< image_->getHeight() << " 255\n";
    outFile.write((char*)image_->getData(), image_->getSize());
    image_->unlock();
    debug(CAMERA, "run: Wrote picture to file\n");
    image_->unlock();
#endif
  }
  debug(CAMERA, "run: Exit\n");
}

void CameraHandler::deleteImage()
{
#if defined(__arm__)
  switch (image_->getType())
  {
    case JPEG:
      delete (ImageJPEG*)image_;
      break;
    case RGB:
      delete (ImageRGB*)image_;
      break;
  }
#endif
}

int CameraHandler::grab()
{
  debug(CAMERA, "grab\n");

#if defined(__arm__)
  int ret = (raspi_cam_ != 0 &&
             raspi_cam_->isOpened() &&
             !raspi_cam_->grab());
  if (ret != 0)
  {
    return ret;
  }
  if (image_ != 0)
  {
    deleteImage();
  }
  image_ = new ImageRGB();
  image_->set(raspi_cam_->getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB),
              raspi_cam_->getWidth(),
              raspi_cam_->getHeight());
  raspi_cam_->retrieve(image_->getData());

  debug(CAMERA, "grab: Create now a jpeg\n");
  ImageRGB* rgb = (ImageRGB*)image_;
  image_        = new ImageJPEG(image_);
  debug(CAMERA, "grab: Reduced size from %d to %d\n", rgb->getSize(), image_->getSize());
  delete rgb;
  return 0;
#endif
  return -1;
}

int CameraHandler::initCamera(raspicam::RaspiCam* camera_handler, struct CameraInfo& info)
{
  debug(CAMERA, "initCamera: width <%d>, heigth <%d>, frame rage <%d>\n", 
    info.width_, info.height_, info.frame_rate_);

#if defined(__arm__)
  camera_handler->setWidth(info.width_);
  camera_handler->setHeight(info.height_);
  camera_handler->setFrameRate(info.frame_rate_);
  return 0;
#endif
  return -1;
}

int CameraHandler::init()
{
  debug(CAMERA, "init\n");
  
#if defined(__arm__)
  lock_.lock();
  raspi_cam_ = new raspicam::RaspiCam();
  if (!raspi_cam_->open())
  {
    debug(WARNING, "CameraHandler::run: Cannot open the camera_handler.\n");
    return -1;
  }

  struct CameraInfo info;
  info.width_       = VGA_WIDTH;
  info.height_      = VGA_HEIGHT;
  info.frame_rate_  = FRAME_RATE;
  int ret;
  if ((ret = initCamera(raspi_cam_, info)) != 0)
  {
    debug(WARNING, "CameraHandler::run: Something seems to be wrong %d\n", ret);
    lock_.unlock(); 
    return -1;
  }
  lock_.unlock(); 
#endif
  return 0;
}