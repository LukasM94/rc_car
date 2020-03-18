#ifndef STATUS_DISPLAY_H
#define STATUS_DISPLAY_H

#include <WorkingThread.h>

class MainWindow;

class StatusDisplay : public WorkingThread
{
  public:
    StatusDisplay(MainWindow* main_window);
    ~StatusDisplay();

    virtual void run();

  private:
    StatusDisplay();
    MainWindow* main_window_;
};

#endif 