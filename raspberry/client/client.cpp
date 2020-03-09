
#include <Control.h>
#include <Atmega.h>
#include <camera.h>
#include <unistd.h>
#include <debug.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <csignal>
#include <config.h>
#include <GamePadClient.h>
#include <GamePadInstance.h>
#include <pthread.h>

pthread_t tid_gp_client;
pthread_t tid_ucontroller;

GamePadClient* gp_client;
Control*       control;
GamePad*       game_pad;
Atmega*        atmega;

void signalHandler(int signal_num);

int main(int argc, char* argv[])
{
  debug(MAIN, "       ---------\n");
  debug(MAIN, "       | Start |\n");
  debug(MAIN, "       ---------\n");

  const char* ip_addr = SERVER_IP;
  const char* port_no = SERVER_PORT;

  debug(MAIN, "main: Initialize the instances\n");
  game_pad  = GamePadInstance::instance()->getGamePad();
  atmega    = new Atmega();
  gp_client = new GamePadClient(atoi(port_no), ip_addr);
  control   = new Control(atmega);

  debug(MAIN, "main: Catch the sigint signal\n");
  signal(SIGINT, signalHandler);  

  debug(MAIN, "main: Create threads\n");
  pthread_create(&tid_gp_client, 0, GamePadClient::runWrapper, gp_client);
  pthread_create(&tid_ucontroller, 0, Control::runWrapper, control);

  debug(MAIN, "main: Goes to sleep\n");
  pthread_join(tid_gp_client, 0);
  pthread_join(tid_ucontroller, 0);

  debug(MAIN, "main: Exits\n");
  return 0;
}

void signalHandler(int signal_num)
{
  debug(MAIN, "signalHandler: Got an signal %d\n", signal_num);
  control->deinit();
  debug(MAIN, "signalHandler: Exits\n");
  _exit(signal_num);
}
