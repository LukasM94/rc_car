
#include <MainWindow.h>
#include <debug.h>
#include <VideoDisplay.h>
#include <string>
#include <unistd.h>
#include <Image.h>
#include <ImageInstance.h>

VideoDisplay::VideoDisplay(MainWindow* main_window) :
  WorkingThread("VideoDisplay", 1),
  main_window_(main_window)
{
  debug(GRAPHICS, "VideoDisplay::ctor: main_window <%p>\n", main_window);
}

VideoDisplay::~VideoDisplay()
{
  debug(GRAPHICS, "VideoDisplay::dtor\n");
}

void VideoDisplay::run()
{
  debug(GRAPHICS, "VideoDisplay::run: Start\n");
  running_ = 1;
  while (running_)
  {
    Image* temp = ImageInstance::instance()->loadImage(1);
    if (temp != 0)
    {
      main_window_->setImage(temp);
      if (image_ != 0)
      {
        delete image_;
      }
      image_ = temp;
    }
  }
  debug(GRAPHICS, "VideoDisplay::run: Exit\n");
}