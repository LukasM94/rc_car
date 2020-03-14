#include <debug.h>
#include <Camera.h>
#include <string.h>
#include <Image.h>
#include <ImageJPEG.h>
#include <ImageRGB.h>
#if defined(__arm__)
#include <raspicam/raspicam.h>
#endif

Camera* Camera::instance_ = 0;

Camera::Camera() :
  image_(0),
  raspi_cam_(0),
  lock_("Camera::lock_"),
  cond_("Camera::cond_")
{
  debug(CAMERA, "ctor\n");
}

Camera::~Camera()
{
#if defined(__arm__)
  if (raspi_cam_ != 0)
  {
    delete raspi_cam_;
  }
#endif
  debug(CAMERA, "dtor\n");
}

Camera* Camera::instance()
{
  if (instance_ == 0)
  {
    instance_ = new Camera();
  }
  return instance_;
}

void Camera::deleteImage()
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

int Camera::grab()
{
  debug(CAMERA, "grab\n");

#if defined(__arm__)
  Image* image;

  int ret = (raspi_cam_ != 0 &&
             raspi_cam_->isOpened() &&
             !raspi_cam_->grab());
  if (ret != 0)
  {
    return ret;
  }
  image = new ImageRGB();
  image->set(raspi_cam_->getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB),
             raspi_cam_->getWidth(),
             raspi_cam_->getHeight());
  raspi_cam_->retrieve(image->getData());

  debug(CAMERA, "grab: Create now a jpeg\n");
  ImageRGB* rgb = (ImageRGB*)image;
  image        = new ImageJPEG(image);
  debug(CAMERA, "grab: Reduced size from %d to %d\n", rgb->getSize(), image->getSize());
  delete rgb;

  lock();
  if (image_ != 0)
  {
    deleteImage();
  }
  image_ = image;
  condLock();
  unlock();
  wake();
  condUnlock();

  return 0;
#endif
  return -1;
}

int Camera::initCamera(raspicam::RaspiCam* camera_handler, struct CameraInfo& info)
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

int Camera::init()
{
  debug(CAMERA, "init\n");
  
#if defined(__arm__)
  lock_.lock();
  raspi_cam_ = new raspicam::RaspiCam();
  if (!raspi_cam_->open())
  {
    debug(WARNING, "Camera::run: Cannot open the camera_handler.\n");
    return -1;
  }

  struct CameraInfo info;
  info.width_       = VGA_WIDTH;
  info.height_      = VGA_HEIGHT;
  info.frame_rate_  = FRAME_RATE;
  int ret;
  if ((ret = initCamera(raspi_cam_, info)) != 0)
  {
    debug(WARNING, "Camera::run: Something seems to be wrong %d\n", ret);
    lock_.unlock(); 
    return -1;
  }
  lock_.unlock(); 
#endif
  return 0;
}