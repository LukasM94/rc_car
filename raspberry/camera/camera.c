
#include <unistd.h>
#include <debug.h>
#include <sys/types.h>

#define PYTHON "python3"

int main()
{
  char* parameter_list[] = {PYTHON, "script/camera.py", NULL};
  debug(CAM, "main: start forking\n");

  pid_t pid = fork();
  if (pid < 0)
  {
    debug(ERROR, "main: fork not possible\n");
  }
  else if (pid == 0)
  {
    debug(CAM, "main: start previewing\n");
    execv(PYTHON, (char* const*)parameter_list);
    debug(ERROR, "main: camera error\n");
  }
}