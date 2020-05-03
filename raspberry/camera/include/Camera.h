#ifndef CAMERA_H
#define CAMERA_H

#include <Lock.h>
#include <Cond.h>

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

class Camera
{
  public:
    static Camera* instance();
    ~Camera();

    int init();
    int deinit();
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
    inline void condLock()
    {
      cond_.lock();
    }
    inline void condUnlock()
    {
      cond_.unlock();
    }
    inline void sleep()
    {
      cond_.sleep();
    }
    inline void wake()
    {
      cond_.wake();
    }

    bool isConnected();
    void deleteImage();

  private:
    Camera();
    static Camera* instance_;

    static int initCamera(raspicam::RaspiCam* camera_handler, struct CameraInfo& info);

    raspicam::RaspiCam* raspi_cam_;

    Image* image_;

    Lock lock_;
    Cond cond_;

    enum CONNECT_STATE
    {
      NOT_INIT,
      CONNECTED,
      NOT_CONNECTED
    };
    enum CONNECT_STATE connected_;
    Cond cond_connected_;

    static const unsigned int QVGA_WIDTH  = 320;
    static const unsigned int QVGA_HEIGHT = 240;
    static const unsigned int VGA_WIDTH   = 640;
    static const unsigned int VGA_HEIGHT  = 480;
    static const unsigned int FRAME_RATE  = 10;
};

#endif