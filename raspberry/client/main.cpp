
#include <ControlHandler.h>
#include <Atmega.h>
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
#include <Control.h>
#include <Camera.h>

pthread_t tid_client_handler;
pthread_t tid_control_handler;
pthread_t tid_camera;

ClientHandler*   client_handler;
ControlHandler*  control_handler;
GamePad*         game_pad;
Atmega*          atmega;
CameraHandler*   camera_handler;
Control*         control;
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
  game_pad         = GamePadInstance::instance()->getGamePad();
  camera           = Camera::instance();
  atmega           = new Atmega();
  control_handler  = new ControlHandler();
  control = Control::instance();
  control->setController(atmega);
  camera_handler   = new CameraHandler();
  client_handler   = new ClientHandler(atoi(port_no), ip_addr);

  debug(MAIN, "main: Catch the sigint signal\n");
  signal(SIGINT, signalHandler);  

  debug(MAIN, "main: Create threads\n");
  pthread_create(&tid_client_handler, 0, ClientHandler::runWrapper, client_handler);
  pthread_create(&tid_control_handler, 0, ControlHandler::runWrapper, control_handler);
  pthread_create(&tid_camera, 0, CameraHandler::runWrapper, camera_handler);

  debug(MAIN, "main: Goes to sleep\n");
  pthread_join(tid_client_handler, 0);
  pthread_join(tid_control_handler, 0);
  pthread_join(tid_camera, 0);

  debug(MAIN, "main: Exits\n");
  return 0;
}

void signalHandler(int signal_num)
{
  debug(MAIN, "signalHandler: Got an signal %d\n", signal_num);
  control_handler->deinit();
  debug(MAIN, "signalHandler: Exits\n");
  _exit(signal_num);
}
