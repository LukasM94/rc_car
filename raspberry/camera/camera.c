
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <debug.h>

#define PYTHON "python"
#define FILE   "/home/pi/Documents/raspberry/camera/script/camera_client.py"

volatile int running = 1;

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    debug(ERROR, "main: usage ./camera <server_ip> <port_no>\n");
    return -1;
  }

  char* server_ip = argv[1];
  char* port      = argv[2];

  char* parameter_list[] = {PYTHON, FILE, server_ip, port, NULL};
  debug(CAM, "main: start forking\n");

  pid_t pid = fork();
  if (pid < 0)
  {
    debug(ERROR, "main: fork not possible\n");
  }
  else if (pid == 0)
  {
    debug(CAM, "main: %s %s %s %s\n", parameter_list[0], parameter_list[1], parameter_list[2], parameter_list[3]);
    execvp(PYTHON, (char* const*)parameter_list);
    debug(ERROR, "main: camera error\n");
    return -1;
  }

  sleep(10);

  // while (running)
  // {
  //   sleep(1);
  // }

  debug(CAM, "main: kill camera process\n");
  kill(pid, SIGKILL);
  debug(CAM, "main: finish successful\n");
  return 0;
}