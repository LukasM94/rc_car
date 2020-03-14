#ifndef XBOX_CONTROLLER_SERVICE_H
#define XBOX_CONTROLLER_SERVICE_H

#include <WorkingThread.h>

class GamePad;
class ServerHandler;

class XboxControllerService : public WorkingThread
{
  public:
    XboxControllerService(ServerHandler* server_handler, GamePad* gamepad);
    ~XboxControllerService();

    inline static void* runWrapper(void* arg)
    {
      reinterpret_cast<XboxControllerService*>(arg)->run();
      return 0;
    }
    virtual void run();

  private:
    XboxControllerService();
    XboxControllerService(const XboxControllerService&);

    ServerHandler* server_handler_;
    GamePad*       gamepad_;
};

#endif