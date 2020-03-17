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

XboxController* xc;
ServerHandler*  server;
ImageInstance*  image_inst;
Graphics*       graphics;

void signalHandler(int signal_num);

int main(int argc, char* argv[])
{

  debug(MAIN, "main: Initialize the instances\n");
  ThreadHandler::init();
  image_inst = ImageInstance::instance();
  xc       = new XboxController(XboxController::DEFAULT_PATH);
  server   = new ServerHandler(SERVER_PORT_INT, xc->getJoystickData());
  graphics = new Graphics();

  debug(MAIN, "main: Catch the sigint signal\n");
  signal(SIGINT, signalHandler);  

  ThreadHandler::lock();

  ThreadHandler::startThread(xc);
  ThreadHandler::startThread(server);
  ThreadHandler::startThread(graphics);

  ThreadHandler::unlock();

  while (1)
  {
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

    debug(MAIN, "main: Goes to sleep for 5 second\n");
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
