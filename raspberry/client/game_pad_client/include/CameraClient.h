#ifndef CAMERA_CLIENT
#define CAMERA_CLIENT

#include <WorkingThread.h>

class ClientHandler;

class CameraClient : public WorkingThread
{
  public:
    CameraClient(ClientHandler* client_handler);
    ~CameraClient();

    inline static void* runWrapper(void* arg)
    {
      reinterpret_cast<CameraClient*>(arg)->run();
      return 0;
    }
    virtual void run();

  private:
    CameraClient();
    CameraClient(const CameraClient&);

    ClientHandler* client_handler_;
};

#endif