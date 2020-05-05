#ifndef CAMERA_HANDLER_H
#define CAMERA_HANDLER_H

#include <WorkingThread.h>

class ClientHandler;

class CameraHandler : public WorkingThread
{
  public:
    ~CameraHandler();

    static CameraHandler* instance();

    virtual void run();

  private:
    CameraHandler();
    CameraHandler(const CameraHandler&);

    unsigned int calculateSleep(ClientHandler* client_handler);

    static CameraHandler* instance_;

    static const int SLEEP = 80000;
};

#endif