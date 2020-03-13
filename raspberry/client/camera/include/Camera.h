#ifndef CAMERA_H
#define CAMERA_H

#include <WorkingThread.h>
#include <Lock.h>

class Image;

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

    inline static void* runWrapper(void* arg)
    {
      reinterpret_cast<Camera*>(arg)->run();
      return 0;
    }
    virtual void run();
    int init();
    int grab();
    unsigned int getWidth();
    unsigned int getHeight();
    unsigned char* getData();
    unsigned int getSize();
    inline Image* getImage()
    {
      return image_;
    }
    inline void lock()
    {
      lock_.lock();
    }
    inline void unlock()
    {
      lock_.unlock();
    }

  private:
    Camera(const Camera&);

    static int initCamera(raspicam::RaspiCam* camera, struct CameraInfo& info);

    void deleteImage();

    raspicam::RaspiCam* raspi_cam_;

    Image* image_;

    Lock lock_;

    static const unsigned int QVGA_WIDTH  = 320;
    static const unsigned int QVGA_HEIGHT = 240;
    static const unsigned int VGA_WIDTH   = 640;
    static const unsigned int VGA_HEIGHT  = 480;
    static const unsigned int FRAME_RATE  = 1;
};

#endif