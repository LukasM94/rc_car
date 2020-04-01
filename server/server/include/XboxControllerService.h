#ifndef XBOX_CONTROLLER_SERVICE_H
#define XBOX_CONTROLLER_SERVICE_H

#include <WorkingThread.h>

class ServerHandler;

class XboxControllerService : public WorkingThread
{
  public:
    XboxControllerService(ServerHandler* server_handler);
    ~XboxControllerService();

    virtual void run();

  private:
    XboxControllerService();
    XboxControllerService(const XboxControllerService&);

    ServerHandler* server_handler_;
};

#endif