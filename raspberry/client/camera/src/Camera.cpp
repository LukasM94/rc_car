#include <debug.h>
#include <Camera.h>
#if defined(__arm__)
#include <raspicam/raspicam.h>
#endif

Camera::Camera() :
  WorkingThread("Camera"),
  camera_(0),
  lock_("Camera::lock_")
{
  debug(CAMERA, "ctor\n");
}

Camera::~Camera()
{
  if (data_ != 0)
  {
    delete data_;
  }
#if defined(__arm__)
  if (camera_ != 0)
  {
    delete camera_;
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

int Camera::catchImage()
{
  debug(CAMERA, "catchImage\n");

#if defined(__arm__)
  return (camera_ != 0 &&
          camera_->isOpen() &&
          camera_->grap());
#endif
  return -1;
}

int Camera::startCapture()
{
  debug(CAMERA, "startCapture\n");

#if defined(__arm__)
  return (camera_ != 0 &&
          camera_->isOpen() &&
          camera_->startCapture());
#endif
  return -1;
}

int Camera::stopCapture()
{
  debug(CAMERA, "stopCapture\n");

#if defined(__arm__)
  return (camera_ != 0 &&
          camera_->isOpen() &&
          camera_->stopCapture());
#endif
  return -1;
}

void* Camera::pictureCallBack(void* arg)
{
  debug(CAMERA, "pictureCallBack: this_camera <%p>\n", arg);
  Camera* this_camera = (Camera*)arg;

#if defined(__arm__)
  this_camera->lock_.lock();
  unsigned char* buffer = this_camera->camera_->getImageBufferData();
  unsigned int   size   = this_camera->camera_->getImageBufferSize();

  memcpy(this_camera->data_, buffer, size);
  this_camera->lock_.unlock();
#endif

  return 0;
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

int Camera::setCallbackFunction(raspicam::RaspiCam* camera, void (*f_ptr)(void*), void* arg)
{
#if defined(__arm__)
  camera->setUserCallback(f_ptr, arg);
  return 0;
#endif
  return -1;
}

int Camera::init()
{
  debug(CAMERA, "init\n");
  
#if defined(__arm__)
  camera_ = new raspicam::RaspiCam();
  int ret;
  if ((ret = camera_->open()) != 0)
  {
    debug(WARNING, "Camera::run: Cannot open the camera. Ret value is %d\n", ret);
  }

  struct CameraInfo info;
  info.width_       = QVGA_WIDTH;
  info.height_      = QVGA_HEIGHT;
  info.frame_rate_  = FRAME_RATE;
  initCamera(info, camera_);
  if (data_ != 0)
  {
    delete data_;
  }
  data_ = new char[camera_->getImageBufferSize(raspicam::RASPICAM_FORMAT_RGB)];
  setCallbackFunction(pictureCallBack, this);
#endif
  return 0;
}