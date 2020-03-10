#include <debug.h>
#include <Camera.h>
#if defined(__arm__)
#include <raspicam/raspicam.h>
#endif

Camera::Camera() :
  WorkingThread("Camera"),
  camera_(0)
{
  debug(CAMERA, "ctor\n");
}

Camera::~Camera()
{
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
#endif
  return 0;
}