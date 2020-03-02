
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <debug.h>
#include <camera.h>

static char PYTHON[]   = "python";
static char CAM_FILE[] = "/home/pi/Documents/raspberry/camera/script/camera_client.py";

int camera(int argc, char* argv[])
{
  if (argc != 3)
  {
    debug(ERROR, "camera: usage ./camera <server_ip> <port_no>\n");
    return -1;
  }

  char* server_ip = argv[1];
  char* port      = argv[2];

  char* parameter_list[] = {PYTHON, CAM_FILE, server_ip, port, 0};
  debug(CAMERA, "camera: start forking\n");

  pid_t pid = fork();
  if (pid < 0)
  {
    debug(ERROR, "camera: fork not possible\n");
  }
  else if (pid == 0)
  {
    debug(CAMERA, "camera: %s %s %s %s\n", parameter_list[0], parameter_list[1], parameter_list[2], parameter_list[3]);
    execvp(PYTHON, (char* const*)parameter_list);
    debug(ERROR, "camera: camera error\n");
    return -1;
  }

  sleep(10);

  kill(pid, SIGKILL);
  debug(CAMERA, "camera: finish successful\n");
  return 0;
}