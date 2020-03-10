#include <debug.h>
#include <Camera.h>

Camera::Camera(unsigned int port) :
  port_(port)
{
  debug(CAMERA, "ctor\n");
}

Camera::~Camera()
{
  debug(CAMERA, "dtor\n");
}