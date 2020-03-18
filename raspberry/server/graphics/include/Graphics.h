#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <WorkingThread.h>

class Graphics: public WorkingThread
{
  public:
    Graphics();
    ~Graphics();

    virtual void run();

  private:
    Graphics(const Graphics&);
};

#endif