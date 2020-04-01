#ifndef VIDEO_DISPLAY_H
#define VIDEO_DISPLAY_H

#include <WorkingThread.h>

class MainWindow;
class Image;

class VideoDisplay : public WorkingThread
{
  public:
    VideoDisplay(MainWindow* main_window);
    ~VideoDisplay();

    virtual void run();

  private:
    VideoDisplay();
    MainWindow* main_window_;
    Image*      image_;
};

#endif 