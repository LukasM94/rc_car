#ifndef CAMERA_CLIENT
#define CAMERA_CLIENT

#include <WorkingThread.h>

class ClientHandler;

class CameraClient : public WorkingThread
{
  public:
    CameraClient(ClientHandler* client_handler);
    ~CameraClient();

    virtual void run();

  private:
    CameraClient();
    CameraClient(const CameraClient&);

    ClientHandler* client_handler_;
};

#endif