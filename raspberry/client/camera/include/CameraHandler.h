#ifndef CAMERA_HANDLER_H
#define CAMERA_HANDLER_H

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
    CameraHandler(const CameraHandler&);

    static int initCamera(raspicam::RaspiCam* camera_handler, struct CameraInfo& info);

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