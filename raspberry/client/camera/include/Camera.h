#ifndef CAMERA_H
#define CAMERA_H

#include <WorkingThread.h>

class Camera : public WorkingThread
{
  public:
    Camera(unsigned int port);
    ~Camera();

  private:
    Camera();
    Camera(const Camera&);

    unsigned int port_;
};

#endif