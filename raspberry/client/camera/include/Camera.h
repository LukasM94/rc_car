#ifndef CAMERA_H
#define CAMERA_H

#include <WorkingThread.h>

namespace raspicam
{
  class RaspiCam;
}

class Camera : public WorkingThread
{
  public:
    Camera();
    ~Camera();

    virtual void run();
    int init();

  private:
    Camera(const Camera&);

    raspicam::RaspiCam* camera_;
};

#endif