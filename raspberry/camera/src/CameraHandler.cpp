#include <debug.h>
#include <CameraHandler.h>
#include <unistd.h>
#include <Camera.h>

CameraHandler::CameraHandler() :
  WorkingThread("CameraHandler")
{
  debug(CAMERA, "ctor\n");
}

CameraHandler::~CameraHandler()
{
  debug(CAMERA, "dtor\n");
}

void CameraHandler::run()
{
  Camera* camera = Camera::instance();
  if (camera->init() != 0)
  {
    debug(CAMERA, "run: Exit camera not connected?\n");
    return;
  }
  else
  {
    debug(CAMERA, "run: Start\n");
  }
  while (running_)
  {
    debug(CAMERA, "run: Sleep %d milli second\n", SLEEP / 1000);
    usleep(SLEEP);

    int ret;
    if ((ret = camera->grab()) != 0)
    {
      debug(WARNING, "camera_handler::run: grab returned %d\n", ret);
    }
    debug(CAMERA, "run: Took picture\n");
  }
  camera->deinit();

  debug(CAMERA, "run: Exit\n");
}