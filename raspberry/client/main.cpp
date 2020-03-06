
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
#include <pthread.h>

pthread_t tid_gp_client;
pthread_t tid_ucontroller;

void signalHandler(int signal_num);

int main(int argc, char* argv[])
{
  debug(MAIN, "       ---------\n");
  debug(MAIN, "       | Start |\n");
  debug(MAIN, "       ---------\n");

  debug(MAIN, "main: Catch the sigint signal\n");
  signal(SIGINT, signalHandler);  

  const char* ip_addr = SERVER_IP;
  const char* port_no = SERVER_PORT;

  debug(MAIN, "main: Initialize the instances\n");
  GamePadClient gp_client(atoi(port_no), ip_addr);
  Atmega* atmega = new Atmega();
  Control control(atmega, gp_client.getGamePad());

  debug(MAIN, "main: Create threads\n");
  pthread_create(&tid_gp_client, 0, GamePadClient::runWrapper, &gp_client);
  pthread_create(&tid_ucontroller, 0, Control::runWrapper, &control);

  debug(MAIN, "main: Goes to sleep\n");
  sleep(1);
  return -2;
  pthread_join(tid_gp_client, 0);
  pthread_join(tid_ucontroller, 0);

  debug(MAIN, "main: Exits\n");
  return 0;
}

void signalHandler(int signal_num)
{
  debug(MAIN, "signalHandler: Got an signal %d\n", signal_num);

  debug(MAIN, "signalHandler: Exits\n");
  _exit(signal_num);
}
