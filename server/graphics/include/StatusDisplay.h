#ifndef STATUS_DISPLAY_H
#define STATUS_DISPLAY_H

#include <QtCore>
#include <atomic>

class MainWindow;

class StatusDisplay : public QThread
{
  public:
    StatusDisplay(MainWindow* main_window);
    ~StatusDisplay();

    void run();
    inline void cancel()
    {
      running_ = 0;
    }

  private:
    StatusDisplay();
    MainWindow* main_window_;
    std::atomic_bool running_;
};


#endif 