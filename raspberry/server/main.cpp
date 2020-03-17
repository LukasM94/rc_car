#include <XboxController.h>
#include <pthread.h>
#include <config.h>
#include <debug.h>
#include <ServerHandler.h>
#include <signal.h>
#include <atomic>
#include <map>
#include <unistd.h>
#include <string.h>
#include <Graphics.h>
#include <ImageInstance.h>

static const char XBOX_CONTROLLER[] = "Xbox controller";
static const char SERVER_NAME[]     = "ServerHandler";
static const char GRAPHICS_NAME[]   = "Graphics";

struct cmp_str
{
   bool operator()(char const *a, char const *b) const
   {
      return strcmp(a, b) < 0;
   }
};
std::map<const char*, pthread_t, cmp_str> tids;
pthread_mutex_t tids_lock = PTHREAD_MUTEX_INITIALIZER;

pthread_t tid_xc;
pthread_t tid_server;
pthread_t tid_graphics;

XboxController* xc;
ServerHandler*  server;
ImageInstance*  image_inst;
Graphics*       graphics;

void atExit(const char* name);
void lockTids();
void unlockTids();
int  addToTids(const char* prime_key, pthread_t tid);
int  removeFromTids(const char* prime_key);
bool isInTids(const char* name);

void signalHandler(int signal_num);

int main(int argc, char* argv[])
{

  debug(MAIN, "main: Initialize the instances\n");
  image_inst = ImageInstance::instance();
  xc       = new XboxController(XboxController::DEFAULT_PATH, XBOX_CONTROLLER);
  server   = new ServerHandler(SERVER_PORT_INT, xc->getJoystickData(), SERVER_NAME);
  graphics = new Graphics(GRAPHICS_NAME);

  debug(MAIN, "main: Catch the sigint signal\n");
  signal(SIGINT, signalHandler);  

  lockTids();
  debug(MAIN, "main: Create threads\n");
  pthread_create(&tid_xc, 0, XboxController::runWrapper, xc);
  pthread_detach(tid_xc);
  pthread_create(&tid_server, 0, ServerHandler::runWrapper, server);
  pthread_detach(tid_server);
  pthread_create(&tid_graphics, 0, Graphics::runWrapper, graphics);
  pthread_detach(tid_graphics);

  debug(MAIN, "main: Add tids to the tidmap\n");
  addToTids(XBOX_CONTROLLER, tid_xc);
  addToTids(SERVER_NAME, tid_server);
  addToTids(GRAPHICS_NAME, tid_graphics);
  unlockTids();
  
  while (1)
  {
    lockTids();
    if (tids.size() != 3)
    {
      if (!isInTids(XBOX_CONTROLLER))
      {
        debug(MAIN, "main: Restart %s thread\n", XBOX_CONTROLLER);
        pthread_create(&tid_xc, 0, XboxController::runWrapper, xc);
        pthread_detach(tid_xc);
        debug(MAIN, "main: Add %s to the tidmap\n", XBOX_CONTROLLER);
        addToTids(XBOX_CONTROLLER, tid_xc);
      }
      if (!isInTids(SERVER_NAME))
      {
        debug(MAIN, "main: Restart %s thread\n", SERVER_NAME);
        pthread_create(&tid_server, 0, ServerHandler::runWrapper, server);
        pthread_detach(tid_server);
        debug(MAIN, "main: Add %s to the tidmap\n", SERVER_NAME);
        addToTids(SERVER_NAME, tid_server);
      }
      if (!isInTids(GRAPHICS_NAME))
      {
        debug(MAIN, "main: Restart %s thread\n", GRAPHICS_NAME);
        pthread_create(&tid_graphics, 0, Graphics::runWrapper, graphics);
        pthread_detach(tid_graphics);
        debug(MAIN, "main: Add %s to the tidmap\n", GRAPHICS_NAME);
        addToTids(GRAPHICS_NAME, tid_graphics);
      }
    }
    unlockTids();
    // debug(MAIN, "main: Goes to sleep for 5 second\n");
    sleep(5);
  }

  debug(MAIN, "main: Exits\n");

  return 0;
}

void signalHandler(int signal_num)
{
  debug(MAIN, "signalHandler: Got an signal %d\n", signal_num);
  server->closeSocket();
  server->closeServerSocket();
  debug(MAIN, "signalHandler: Exits\n");
  _exit(signal_num);
}

void atExit(const char* name)
{
  lockTids();
  removeFromTids(name);
  unlockTids();
}

void lockTids()
{
  pthread_mutex_lock(&tids_lock);
}

void unlockTids()
{
  pthread_mutex_unlock(&tids_lock);
}

int addToTids(const char* prime_key, pthread_t tid)
{
  auto it = tids.find(prime_key);
  if (it != tids.end())
  {
    debug(WARNING, "main::addToTids: Already in tids map <%s>\n", prime_key);
    return -1;
  }
  debug(MAIN, "addToTids: Added <%s>\n", prime_key);
  tids[prime_key] = tid;
  return 0;
}

int removeFromTids(const char* prime_key)
{
  auto it = tids.find(prime_key);
  if (it == tids.end())
  {
    debug(WARNING, "main::removeFromTids: Not in tids map <%s>\n", prime_key);
    return -1;
  }
  debug(MAIN, "removeFromTids: Removed <%s>\n", prime_key);
  tids.erase(prime_key);
  return 0;
}

bool isInTids(const char* name)
{
  return (tids.find(name) != tids.end());
}
