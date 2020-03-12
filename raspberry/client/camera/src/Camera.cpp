#include <debug.h>
#include <Camera.h>
#include <string.h>
#include <Image.h>
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
  debug(CAMERA, "run: Start\n");
  while (running_)
  {

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
  image_ = new Image(raspi_cam_->getImageBufferData(),
                     raspi_cam_->getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB),
                     raspi_cam_->getWidth(),
                     raspi_cam_->getHeight());
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

  // struct CameraInfo info;
  // info.width_       = QVGA_WIDTH;
  // info.height_      = QVGA_HEIGHT;
  // info.frame_rate_  = FRAME_RATE;
  // int ret;
  // if ((ret = initCamera(raspi_cam_, info)) != 0)
  // {
  //   debug(WARNING, "Camera::run: Something seems to be wrong %d\n", ret);
  //   lock_.unlock(); 
  //   return -1;
  // }
  lock_.unlock(); 
#endif
  return 0;
}