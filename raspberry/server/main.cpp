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

static const char XBOX_CONTROLLER[] = "Xbox controller";
static const char SERVER_NAME[]     = "ServerHandler";

pthread_mutex_t tids_lock = PTHREAD_MUTEX_INITIALIZER;
struct cmp_str
{
   bool operator()(char const *a, char const *b) const
   {
      return strcmp(a, b) < 0;
   }
};
std::map<const char*, pthread_t, cmp_str> tids;

void atExit(const char* name);

void lockTids();
void unlockTids();
int  addToTids(const char* prime_key, pthread_t tid);
int  removeFromTids(const char* prime_key);
bool isInTids(const char* name);

int main(int argc, char* argv[])
{
  pthread_t tid_xc;
  pthread_t tid_server;

  debug(MAIN, "main: Initialize the instances\n");
  XboxController xc(XboxController::DEFAULT_PATH, XBOX_CONTROLLER);
  ServerHandler server(SERVER_PORT_INT, xc.getJoystickData(), SERVER_NAME);

  lockTids();
  debug(MAIN, "main: Create threads\n");
  pthread_create(&tid_xc, 0, XboxController::runWrapper, &xc);
  pthread_detach(tid_xc);
  pthread_create(&tid_server, 0, ServerHandler::runWrapper, &server);
  pthread_detach(tid_server);

  debug(MAIN, "main: Add tids to the tidmap\n");
  addToTids(XBOX_CONTROLLER, tid_xc);
  addToTids(SERVER_NAME, tid_server);
  unlockTids();
  
  while (1)
  {
    lockTids();
    if (tids.size() != 2)
    {
      if (!isInTids(XBOX_CONTROLLER))
      {
        debug(MAIN, "main: Restart %s thread\n", XBOX_CONTROLLER);
        xc.init();
        pthread_create(&tid_xc, 0, XboxController::runWrapper, &xc);
        pthread_detach(tid_xc);
        debug(MAIN, "main: Add %s to the tidmap\n", XBOX_CONTROLLER);
        addToTids(XBOX_CONTROLLER, tid_xc);
      }
      if (!isInTids(SERVER_NAME))
      {
        debug(MAIN, "main: Restart %s thread\n", SERVER_NAME);
        pthread_create(&tid_server, 0, ServerHandler::runWrapper, &server);
        pthread_detach(tid_server);
        debug(MAIN, "main: Add %s to the tidmap\n", SERVER_NAME);
        addToTids(SERVER_NAME, tid_server);
      }
    }
    unlockTids();
    // debug(MAIN, "main: Goes to sleep for 5 second\n");
    sleep(5);
  }

  debug(MAIN, "main: Exits\n");

  return 0;
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
