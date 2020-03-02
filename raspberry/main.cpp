
#include <control.h>
#include <camera.h>
#include <xbox_controller.h>
#include <unistd.h>
#include <debug.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <csignal>

pid_t pid_control;
pid_t pid_camera;
pid_t pid_xbox_controller;

void signalHandler(int signal_num);

int main(int argc, char* argv[])
{
  debug(MAIN, "       ---------\n");
  debug(MAIN, "       | Start |\n");
  debug(MAIN, "       ---------\n");

  debug(MAIN, "main: Catch the sigint signal\n");
  signal(SIGINT, signalHandler);  

  if (argc != 4)
  {
    debug(ERROR, "main: Usage ./main <server_ip> <port_no_camera> <port_no_xbox_controller>\n");
    return -1;
  }
  char* server_ip               = argv[1];
  char* port_no_camera          = argv[2];
  char* port_no_xbox_controller = argv[3];

  pid_control = fork();
  if (pid_control < 0)
  {
    debug(ERROR, "main: Control process cannot be created\n");
    return -1;
  }
  else if (pid_control == 0)
  {
    debug(MAIN, "main: Start control process\n");
    int ret = control(0, 0);
    debug(MAIN, "main: Control process exited %d\n", ret);
    return ret;
  }

  pid_camera = fork();
  if (pid_camera < 0)
  {
    debug(ERROR, "main: Camera process cannot be created\n");
    return -1;
  }
  else if (pid_camera == 0)
  {
    debug(MAIN, "main: Start camera process\n");
    debug(MAIN, "main: server_ip <%s>\n", server_ip);
    debug(MAIN, "main: port_no   <%s>\n", port_no_camera);
    char* arg[] = {"./camera", server_ip, port_no_camera, NULL};
    int ret = camera(3, arg);
    debug(MAIN, "main: Camera process exited %d\n", ret);
    return ret;
  }

  pid_xbox_controller = fork();
  if (pid_xbox_controller < 0)
  {
    debug(ERROR, "main: Camera process cannot be created\n");
    return -1;
  }
  else if (pid_xbox_controller == 0)
  {
    debug(MAIN, "main: Start xbox process\n");
    debug(MAIN, "main: server_ip <%s>\n", server_ip);
    debug(MAIN, "main: port_no   <%s>\n", port_no_xbox_controller);
    char* arg[] = {"./xbox_controller", server_ip, port_no_xbox_controller, NULL};
    int ret = xbox_controller(3, arg);
    debug(MAIN, "main: Xbox controller process exited %d\n", ret);
    return ret;
  }

  debug(MAIN, "main: Wait till all proesses are finished\n");

  waitpid(pid_camera, 0, 0);
  waitpid(pid_control, 0, 0);
  waitpid(pid_xbox_controller, 0, 0);

  debug(MAIN, "main: Exits\n");
  return 0;
}

void signalHandler(int signal_num)
{
  debug(MAIN, "signalHandler: Got an signal %d\n", signal_num);

  kill(pid_camera, SIGINT);
  kill(pid_control, SIGINT);
  kill(pid_xbox_controller, SIGINT);

  debug(MAIN, "signalHandler: Exits\n");
  _exit(signal_num);
}
