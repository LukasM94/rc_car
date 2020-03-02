
#include <control.h>
#include <camera.h>
#include <unistd.h>
#include <debug.h>
#include <sys/wait.h>
#include <sys/types.h>

pid_t pid_control;
pid_t pid_camera;

int main(int argc, char* argv[])
{
  debug(MAIN, "       ---------\n");
  debug(MAIN, "       | Start |\n");
  debug(MAIN, "       ---------\n");

  if (argc != 3)
  {
    debug(ERROR, "main: Usage ./main <server_ip> <port_no>\n");
    return -1;
  }

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
    char* server_ip = argv[1];
    char* port_no   = argv[2];

    debug(MAIN, "main: Start camera process\n");
    debug(MAIN, "main: server_ip <%s>\n", server_ip);
    debug(MAIN, "main: port_no   <%s>\n", port_no);
    int ret = camera(argc, argv);
    debug(MAIN, "main: Camera process exited %d\n", ret);
    return ret;
  }

  debug(MAIN, "main: Wait till all proesses are finished\n");

  int status;
  // waitpid(pid_camera, &status, 0);
  waitpid(pid_control, &status, 0);

  debug(MAIN, "main: Exits\n");
  return 0;
}