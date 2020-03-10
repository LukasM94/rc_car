#ifndef GAME_PAD_CLIENT
#define GAME_PAD_CLIENT

#include <Socket.h>
#include <WorkingThread.h>

class GamePad;

class GamePadClient : public Socket, public WorkingThread
{
  public:
    GamePadClient(unsigned int server_port, const char* server_ip);
    ~GamePadClient();

    inline static void* runWrapper(void* arg)
    {
      reinterpret_cast<GamePadClient*>(arg)->run();
      return 0;
    }
    virtual void run();

    virtual int init();
    virtual int receive();
    virtual int transmit();
    int connectToServer();

  private:
    GamePadClient();
    GamePadClient(const GamePadClient&);

    int server_socket_;

    static const char HELLO[];
};

#endif