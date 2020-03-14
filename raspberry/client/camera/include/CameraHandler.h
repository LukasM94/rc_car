#ifndef CAMERA_HANDLER_H
#define CAMERA_HANDLER_H

#include <WorkingThread.h>

class CameraHandler : public WorkingThread
{
  public:
    CameraHandler();
    ~CameraHandler();

    inline static void* runWrapper(void* arg)
    {
      reinterpret_cast<CameraHandler*>(arg)->run();
      return 0;
    }
    virtual void run();

  private:
    CameraHandler(const CameraHandler&);
};

#endif