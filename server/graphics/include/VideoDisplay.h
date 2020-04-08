#ifndef VIDEO_DISPLAY_H
#define VIDEO_DISPLAY_H

#include <QtCore>
#include <atomic>

class MainWindow;
class Image;

class VideoDisplay : public QThread
{
  public:
    VideoDisplay(MainWindow* main_window);
    ~VideoDisplay();

    void run();
    inline void cancel()
    {
      running_ = 0;
    }

  private:
    VideoDisplay();
    MainWindow* main_window_;
    Image*      image_;

    std::atomic_bool running_;
};

#endif 