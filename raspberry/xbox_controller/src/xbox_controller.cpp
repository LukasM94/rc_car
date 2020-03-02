
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <debug.h>
#include <xbox_controller.h>

static char PYTHON[]               = "python3";
static char XBOX_CONTROLLER_FILE[] = "/home/pi/Documents/raspberry/xbox_controller/script/xbox_controller_client.py";

int xbox_controller(int argc, char* argv[])
{
if (argc != 3)
  {
    debug(ERROR, "xbox_controller: usage ./xbox_controller <server_ip> <port_no>\n");
    return -1;
  }

  char* server_ip = argv[1];
  char* port      = argv[2];

  char* parameter_list[] = {PYTHON, XBOX_CONTROLLER_FILE, server_ip, port, 0};
  debug(XBOX_CONTR, "xbox_controller: start forking\n");

  pid_t pid = fork();
  if (pid < 0)
  {
    debug(XBOX_CONTR, "xbox_controller: fork not possible\n");
  }
  else if (pid == 0)
  {
    debug(XBOX_CONTR, "xbox_controller: %s %s %s %s\n", parameter_list[0], parameter_list[1], parameter_list[2], parameter_list[3]);
    execvp(PYTHON, (char* const*)parameter_list);
    debug(ERROR, "xbox_controller: xbox_controller error\n");
    return -1;
  }

  sleep(20);

  kill(pid, SIGKILL);
  debug(XBOX_CONTR, "xbox_controller: finish successful\n");
  return 0;
}


