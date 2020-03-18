
#include <MainWindow.h>
#include <debug.h>
#include <StatusDisplay.h>
#include <string>
#include <unistd.h>
#include <GamePad.h>
#include <GamePadInstance.h>

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
  std::string data;
  while (running_)
  {
    game_pad->getPrintableString(data);
    main_window_->setStatusLeft(data);
    usleep(100000);
  }
  data = "";
  main_window_->setStatusLeft(data);
  debug(GRAPHICS, "StatusDisplay::run: Exit\n");
}