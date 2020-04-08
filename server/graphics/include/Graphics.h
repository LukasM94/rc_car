#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <WorkingThread.h>

class Graphics: public WorkingThread
{
  public:
    ~Graphics();

    static Graphics* instance();

    virtual void run();

  private:
    Graphics();
    Graphics(const Graphics&);

    static Graphics* instance_;
};

#endif