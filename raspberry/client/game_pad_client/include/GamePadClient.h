#ifndef GAME_PAD_CLIENT
#define GAME_PAD_CLIENT

#include <WorkingThread.h>

class GamePad;
class ClientHandler;

class GamePadClient : public WorkingThread
{
  public:
    GamePadClient(ClientHandler* client_handler);
    ~GamePadClient();

    inline static void* runWrapper(void* arg)
    {
      reinterpret_cast<GamePadClient*>(arg)->run();
      return 0;
    }
    virtual void run();

  private:
    GamePadClient();
    GamePadClient(const GamePadClient&);

    ClientHandler* client_handler_;

    static const char HELLO[];
};

#endif