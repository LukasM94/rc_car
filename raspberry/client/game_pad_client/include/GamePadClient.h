#ifndef GAME_PAD_CLIENT
#define GAME_PAD_CLIENT

#include <string>
#include <atomic>
#include <Socket.h>

class GamePad;

class GamePadClient : public Socket
{
  public:
    GamePadClient(unsigned int server_port, const char* server_ip);
    ~GamePadClient();

    inline static void* runWrapper(void* arg)
    {
      reinterpret_cast<GamePadClient*>(arg)->run();
      return 0;
    }
    void run();
    inline void cancel()
    {
      running_ = 0;
    }

    virtual int init();
    virtual int receive();
    virtual int transmit();
    int connectToServer();

  private:
    GamePadClient();
    GamePadClient(const GamePadClient&);

    int server_socket_;

    GamePad* game_pad_;

    std::atomic_bool running_;

    static const char HELLO[];
};

#endif