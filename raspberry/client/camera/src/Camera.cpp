#include <debug.h>
#include <Camera.h>
#include <string.h>
#include <Image.h>
#include <ImageJPEG.h>
#include <ImageRGB.h>
#include <fstream>
#if defined(__arm__)
#include <raspicam/raspicam.h>
#endif

Camera::Camera() :
  WorkingThread("Camera"),
  image_(0),
  raspi_cam_(0),
  lock_("Camera::lock_")
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

void Camera::run()
{
  init();
  debug(CAMERA, "run: Start\n");
  while (running_)
  {
    lock();
    grab();
    Image* image = getImage();
    debug(CAMERA, "run: Took picture\n");
    image->lock();
    unlock();
    std::ofstream outFile ("raspicam_image.ppm",std::ios::binary);
	  outFile << "P6\n" << image->getWidth() <<" "<< image->getHeight() << " 255\n";
    outFile.write((char*)image->getData(), image->getSize());
    image->unlock();
    debug(CAMERA, "run: Wrote picture to file\n");
    delete image;
  }
  debug(CAMERA, "run: Exit\n");
}

int Camera::grab()
{
  debug(CAMERA, "grab\n");

#if defined(__arm__)
  int ret = (raspi_cam_ != 0 &&
             raspi_cam_->isOpened() &&
             !raspi_cam_->grab());
  if (ret != 0)
  {
    return -1;
  }
  image_ = new ImageRGB();
  image_->set(raspi_cam_->getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB),
              raspi_cam_->getWidth(),
              raspi_cam_->getHeight());
  raspi_cam_->retrieve(image_->getData());
#endif
  return -1;
}

int Camera::initCamera(raspicam::RaspiCam* camera, struct CameraInfo& info)
{
  debug(CAMERA, "initCamera: width <%d>, heigth <%d>, frame rage <%d>\n", 
    info.width_, info.height_, info.frame_rate_);

#if defined(__arm__)
  camera->setWidth(info.width_);
  camera->setHeight(info.height_);
  camera->setFrameRate(info.frame_rate_);
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
    debug(WARNING, "Camera::run: Cannot open the camera.\n");
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