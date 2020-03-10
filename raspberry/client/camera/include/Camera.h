#ifndef CAMERA_H
#define CAMERA_H

class Camera
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