#include <XboxController.h>
#include <pthread.h>
#include <config.h>
#include <debug.h>
#include <Server.h>
#include <signal.h>
#include <atomic>

int main(int argc, char* argv[])
{
  pthread_t tid_xc;
  pthread_t tid_server;

  debug(MAIN, "main: Initialize the instances\n");
  XboxController xc(XboxController::DEFAULT_PATH);
  Server server(SERVER_PORT, xc.getJoystickData());

  debug(MAIN, "main: Create threads\n");
  pthread_create(&tid_xc, 0, XboxController::runWrapper, &xc);
  pthread_create(&tid_server, 0, Server::runWrapper, &server);
  
  debug(MAIN, "main: Goes to sleep\n");
  pthread_join(tid_xc, 0);
  pthread_join(tid_server, 0);

  debug(MAIN, "main: Exits\n");

  return 0;
}
