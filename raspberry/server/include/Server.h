#ifndef SERVER_H
#define SERVER_H

#include <atomic>
#include <netinet/in.h> 
#include <Socket.h>

class GamePad;

class Server : public Socket
{
  public:
    Server(unsigned int port, GamePad* gamepad);
    ~Server();

    inline static void* runWrapper(void* arg)
    {
      reinterpret_cast<Server*>(arg)->run();
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
    int listenAndAccept();

  private:
    Server();
    Server(const Server&);

    int socket_;
    int client_socket_;

    GamePad* gamepad_;

    std::atomic_bool running_;
};

#endif