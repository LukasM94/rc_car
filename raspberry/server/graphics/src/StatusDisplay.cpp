
#include <MainWindow.h>
#include <debug.h>
#include <StatusDisplay.h>
#include <string>
#include <unistd.h>
#include <GamePad.h>
#include <GamePadInstance.h>
#include <TransceivedDataInstance.h>

StatusDisplay::StatusDisplay(MainWindow* main_window) :
  WorkingThread("StatusDisplay", 1),
  main_window_(main_window)
{
  debug(GRAPHICS, "StatusDisplay::ctor: main_window <%p>\n", main_window);
}

StatusDisplay::~StatusDisplay()
{
  debug(GRAPHICS, "StatusDisplay::dtor\n");
}

void StatusDisplay::run()
{
  debug(GRAPHICS, "StatusDisplay::run: Start\n");
  GamePad* game_pad = GamePadInstance::instance()->getGamePad();
  running_ = 1;
  int count = 0;
  unsigned long received_bytes_old    = 0;
  unsigned long transmitted_bytes_old = 0;
  unsigned long received_images_old   = 0;
  unsigned long received_bytes        = 0;
  unsigned long transmitted_bytes     = 0;
  unsigned long received_images       = 0;
  std::string data;
  TransceivedDataInstance::instance()->reset();
  while (running_)
  {
    game_pad->getPrintableString(data);
    main_window_->setStatusLeft(data);
    if (++count == 10)
    {
      received_bytes    = TransceivedDataInstance::instance()->getReceivedBytes();
      transmitted_bytes = TransceivedDataInstance::instance()->getTransmittedBytes();
      received_images   = TransceivedDataInstance::instance()->getReceivedImages();

      data = "rxd: " + std::to_string((received_bytes - received_bytes_old) / 1000) + " kB/sec " +
             "txd: " + std::to_string((transmitted_bytes - transmitted_bytes_old) / 1000) + " kB/sec\n" +
             std::to_string(received_images - received_images_old) + " frames/sec\n";
      main_window_->setStatusRight(data);
      received_bytes_old = received_bytes;
      transmitted_bytes_old = transmitted_bytes;
      received_images_old = received_images;
      count = 0;
    }
    usleep(100000);
  }
  data = "";
  main_window_->setStatusLeft(data);
  main_window_->setStatusRight(data);
  debug(GRAPHICS, "StatusDisplay::run: Exit\n");
}