#ifndef CAMERA_H
#define CAMERA_H

#include <WorkingThread.h>

class Camera : public WorkingThread
{
  public:
    Camera(unsigned int port);
    ~Camera();

    virtual void run();
    void init();

  private:
    Camera();
    Camera(const Camera&);

    unsigned int port_;
};

#endif