#ifndef CAMERA_H
#define CAMERA_H

#include <WorkingThread.h>
#include <Lock.h>

namespace raspicam
{
  class RaspiCam;
}

struct CameraInfo
{
  unsigned int width_;
  unsigned int height_;
  unsigned int frame_rate_;
};

class Camera : public WorkingThread
{
  public:
    Camera();
    ~Camera();

    virtual void run();
    int init();

    int catchImage();
    int startCapture();

  private:
    Camera(const Camera&);

    static void* pictureCallBack(void* arg);

    static int initCamera(raspicam::RaspiCam* camera, struct CameraInfo& info);

    raspicam::RaspiCam* camera_;

    unsigned char* data_;

    Lock  lock_;

    static const unsigned int QVGA_WIDTH  = 320;
    static const unsigned int QVGA_HEIGHT = 240;
    static const unsigned int VGA_WIDTH   = 640;
    static const unsigned int VGA_HEIGHT  = 480;
    static const unsigned int FRAME_RATE  = 1;
};

#endif