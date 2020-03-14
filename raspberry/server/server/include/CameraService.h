#ifndef CAMERA_SERVICE_H
#define CAMERA_SERVICE_H

#include <WorkingThread.h>

class ServerHandler;
class Image;

class CameraService : public WorkingThread
{
  public:
    CameraService(ServerHandler* server_handler);
    ~CameraService();

    inline static void* runWrapper(void* arg)
    {
      reinterpret_cast<CameraService*>(arg)->run();
      return 0;
    }
    virtual void run();

  private:
    CameraService();
    CameraService(const CameraService&);

    ServerHandler* server_handler_;
    Image*         image_;
};

#endif