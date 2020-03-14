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

  private:
    Camera();
    static Camera* instance_;

    // ImageJPEG* jpeg = (ImageJPEG*)image_;
    // image_          = new ImageRGB(image_);
    // debug(CAMERA, "grab: Got the rgb back %d to %d\n", jpeg->getSize(), image_->getSize());
    // delete jpeg;
    // std::ofstream outFile ("raspicam_image.ppm",std::ios::binary);
	  // outFile << "P6\n" << image_->getWidth() <<" "<< image_->getHeight() << " 255\n";
    // outFile.write((char*)image_->getData(), image_->getSize());
    // debug(CAMERA, "run: Wrote picture to file\n");

    static int initCamera(raspicam::RaspiCam* camera_handler, struct CameraInfo& info);

    void deleteImage();

    raspicam::RaspiCam* raspi_cam_;

    Image* image_;

    Lock lock_;
    Cond cond_;

    static const unsigned int QVGA_WIDTH  = 320;
    static const unsigned int QVGA_HEIGHT = 240;
    static const unsigned int VGA_WIDTH   = 640;
    static const unsigned int VGA_HEIGHT  = 480;
    static const unsigned int FRAME_RATE  = 1;
};

#endif