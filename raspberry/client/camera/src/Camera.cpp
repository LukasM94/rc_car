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