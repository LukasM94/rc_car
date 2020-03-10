#include <debug.h>
#include <Camera.h>

Camera::Camera(unsigned int port) :
  WorkingThread("Camera"),
  port_(port)
{
  debug(CAMERA, "ctor: port <%d>\n", port_);
}

Camera::~Camera()
{
  debug(CAMERA, "dtor\n");
}

void Camera::run()
{
  debug(CAMERA, "run: Start\n");
  debug(CAMERA, "run: Exit\n");
}

void Camera::init()
{
  debug(CAMERA, "init\n");
}