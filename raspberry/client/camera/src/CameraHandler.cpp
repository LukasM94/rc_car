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
  camera->init();
  debug(CAMERA, "run: Start\n");
  while (running_)
  {
    debug(CAMERA, "run: Sleep 1 second\n");
    sleep(1);

    int ret;
    camera->lock();
    if ((ret = camera->grab()) != 0)
    {
      debug(WARNING, "camera_handler::run: grab returned %d\n", ret);
    }
    debug(CAMERA, "run: Took picture\n");
    camera->unlock();
  }
  debug(CAMERA, "run: Exit\n");
}