
#include <ControlHandler.h>
#include <unistd.h>
#include <debug.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <csignal>
#include <config.h>
#include <ClientHandler.h>
#include <GamePadInstance.h>
#include <pthread.h>
#include <fstream>
#include <CameraHandler.h>
#include <Image.h>
#include <Camera.h>
#include <ThreadHandler.h>
#include <client_config.h>

ClientHandler*   client_handler;
ControlHandler*  control_handler;
GamePad*         game_pad;
CameraHandler*   camera_handler;
Camera*          camera;

void signalHandler(int signal_num);

int main(int argc, char* argv[])
{
  debug(MAIN, "       ---------\n");
  debug(MAIN, "       | Start |\n");
  debug(MAIN, "       ---------\n");

  const char* ip_addr = SERVER_IP;
  const char* port_no = SERVER_PORT;

  debug(MAIN, "main: Initialize the instances\n");
  ThreadHandler::init();
  game_pad         = GamePadInstance::instance()->getGamePad();
  camera           = Camera::instance();
  control_handler  = new ControlHandler();
  camera_handler   = new CameraHandler();
  client_handler   = new ClientHandler(atoi(port_no), ip_addr);

  debug(MAIN, "main: Catch the sigint signal\n");
  signal(SIGINT, signalHandler);  

  ThreadHandler::lock();
  ThreadHandler::beginThread(client_handler);
  ThreadHandler::beginThread(control_handler);
  // ThreadHandler::beginThread(camera_handler);
  ThreadHandler::startExternThread(camera_handler);
  ThreadHandler::unlock();

  while (1)
  {
    sleep(CLIENT_SLEEP_TIME);

    debug(MAIN, "main: Goes to sleep\n");
    ThreadHandler::gotoSleep();
    debug(MAIN, "main: Got up\n");

    ThreadHandler::lock();
    if (ThreadHandler::isThreadRunning(client_handler) == false)
    {
      ThreadHandler::startThread(client_handler);
    }
    if (ThreadHandler::isThreadRunning(control_handler) == false)
    {
      ThreadHandler::startThread(control_handler);
    }
    // if (ThreadHandler::isThreadRunning(camera_handler) == false)
    // {
    //   ThreadHandler::startThread(camera_handler);
    // }
    ThreadHandler::printThreads();
    ThreadHandler::unlock();
  }
  debug(MAIN, "main: Exits\n");
  return 0;
}

void signalHandler(int signal_num)
{
  debug(MAIN, "signalHandler: Got an signal %d\n", signal_num);
  client_handler->closeSocket();
  control_handler->deinit();
  debug(MAIN, "signalHandler: Exits\n");
  _exit(signal_num);
}
