#ifndef CAMERA_SERVICE_H
#define CAMERA_SERVICE_H

#include <WorkingThread.h>

class ServerHandler;
class Image;
struct ImageJsonData;

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

    void stateStart();
    void stateHeader();
    void stateBody();
    void stateEnd();

    enum State
    {
      START,
      HEADER,
      BODY,
      END,
      ERROR
    };

    struct ImageJsonData* image_json_data_;

    enum State      state_;
    ServerHandler*  server_handler_;
    Image*          image_;
};

#endif