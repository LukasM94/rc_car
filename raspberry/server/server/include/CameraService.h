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

    virtual void run();

  private:
    CameraService();
    CameraService(const CameraService&);

    void stateStart();
    void stateHeader();
    void stateBody();
    void stateConvert();

    enum State
    {
      START,
      HEADER,
      BODY,
      CONVERT,
      END,
      ERROR
    };

    struct ImageJsonData* image_json_data_;

    enum State      state_;
    ServerHandler*  server_handler_;
    Image*          image_;
};

#endif