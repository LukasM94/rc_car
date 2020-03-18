#include <XboxController.h>
#include <pthread.h>
#include <config.h>
#include <debug.h>
#include <ServerHandler.h>
#include <signal.h>
#include <atomic>
#include <map>
#include <unistd.h>
#include <string.h>
#include <Graphics.h>
#include <ImageInstance.h>
#include <ThreadHandler.h>
#include <GamePadInstance.h>
#include <TransceivedDataInstance.h>

XboxController*  xc;
ServerHandler*   server;
ImageInstance*   image_inst;
Graphics*        graphics;
GamePadInstance* game_pad_inst;
TransceivedDataInstance* trans_data_inst;

void signalHandler(int signal_num);

int main(int argc, char* argv[])
{

  debug(MAIN, "main: Initialize the instances\n");

  ThreadHandler::init();

  image_inst      = ImageInstance::instance();
  game_pad_inst   = GamePadInstance::instance();
  trans_data_inst = TransceivedDataInstance::instance();

  xc       = new XboxController(XboxController::DEFAULT_PATH);
  server   = new ServerHandler(SERVER_PORT_INT);
  graphics = new Graphics();

  debug(MAIN, "main: Catch the sigint signal\n");
  signal(SIGINT, signalHandler);  

  ThreadHandler::lock();

  ThreadHandler::beginThread(xc);
  ThreadHandler::beginThread(server);
  ThreadHandler::beginThread(graphics);

  ThreadHandler::unlock();

  while (1)
  {
    debug(MAIN, "main: Goes to sleep\n");
    ThreadHandler::gotoSleep();
    debug(MAIN, "main: Got up\n");

    ThreadHandler::lock();
    if (ThreadHandler::isThreadRunning(xc) == false)
    {
      ThreadHandler::startThread(xc);
    }
    if (ThreadHandler::isThreadRunning(server) == false)
    {
      ThreadHandler::startThread(server);
    }
    if (ThreadHandler::isThreadRunning(graphics) == false)
    {
      ThreadHandler::startThread(graphics);
    }
    ThreadHandler::unlock();

    sleep(5);
  }
  debug(MAIN, "main: Exits\n");

  return 0;
}

void signalHandler(int signal_num)
{
  debug(MAIN, "signalHandler: Got an signal %d\n", signal_num);
  server->closeSocket();
  server->closeServerSocket();
  debug(MAIN, "signalHandler: Exits\n");
  _exit(signal_num);
}
