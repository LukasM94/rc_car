#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h> 
#include <Socket.h>
#include <WorkingThread.h>

class GamePad;

class Server : public Socket, public WorkingThread
{
  public:
    Server(unsigned int port, GamePad* gamepad, const char* name);
    ~Server();

    inline static void* runWrapper(void* arg)
    {
      reinterpret_cast<Server*>(arg)->run();
      return 0;
    }
    virtual void run();

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
};

#endif