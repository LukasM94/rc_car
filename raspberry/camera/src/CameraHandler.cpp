#include <debug.h>
#include <CameraHandler.h>
#include <unistd.h>
#include <Camera.h>
#include <ClientHandler.h>

CameraHandler* CameraHandler::instance_ = 0;

CameraHandler::CameraHandler() :
  WorkingThread("CameraHandler")
{
  debug(CAMERA, "ctor\n");
}

CameraHandler::~CameraHandler()
{
  debug(CAMERA, "dtor\n");
}

CameraHandler* CameraHandler::instance()
{
  if (instance_ == 0)
  {
    instance_ = new CameraHandler();
  }
  return instance_;
}

unsigned int CameraHandler::calculateSleep(ClientHandler* client_handler)
{
  return SLEEP;
}

void CameraHandler::run()
{
  Camera*        camera         = Camera::instance();
  ClientHandler* client_handler = ClientHandler::instance();

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
    unsigned int sleep = calculateSleep(client_handler);
    debug(CAMERA, "run: Sleep %d milli second\n", sleep / 1000);
    usleep(sleep);

    int ret;
    if (client_handler->isConnected() && (ret = camera->grab()) != 0)
    {
      debug(WARNING, "camera_handler::run: grab returned %d\n", ret);
    }
    debug(CAMERA, "run: Took picture\n");
  }
  camera->deinit();

  debug(CAMERA, "run: Exit\n");
}