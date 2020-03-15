#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <WorkingThread.h>

class QApplication;
class QImage;
class QLabel;
class Image;

class Graphics: public WorkingThread
{
  public:
    Graphics();
    ~Graphics();

    inline static void* runWrapper(void* arg)
    {
      reinterpret_cast<Graphics*>(arg)->run();
      return 0;
    }
    virtual void run();

  private:
    Graphics(const Graphics&);

    int    argv_;
    char** argc_;

    QApplication* app_;
    QImage*       graph_;
    QLabel*       label_;

    Image* image_;
};

#endif