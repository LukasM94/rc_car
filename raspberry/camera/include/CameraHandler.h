#ifndef CAMERA_HANDLER_H
#define CAMERA_HANDLER_H

#include <WorkingThread.h>

class CameraHandler : public WorkingThread
{
  public:
    CameraHandler();
    ~CameraHandler();

    virtual void run();

  private:
    CameraHandler(const CameraHandler&);

    static const int SLEEP = 40000;
};

#endif