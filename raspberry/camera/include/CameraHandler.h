#ifndef CAMERA_HANDLER_H
#define CAMERA_HANDLER_H

#include <WorkingThread.h>

class CameraHandler : public WorkingThread
{
  public:
    ~CameraHandler();

    static CameraHandler* instance();

    virtual void run();

  private:
    CameraHandler();
    CameraHandler(const CameraHandler&);

    static CameraHandler* instance_;

    static const int SLEEP = 40000;
};

#endif