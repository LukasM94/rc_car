#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <Socket.h>
#include <WorkingThread.h>

class ClientHandler : public WorkingThread, public Socket 
{
  public:
    ClientHandler(unsigned int server_port, const char* server_ip);
    ~ClientHandler();

    virtual void run();

    virtual int initSocket();
    virtual int receive();
    virtual int transmit();
    virtual int closeSocket();

    int connectToServer();

  private:
    friend class GamePadClient;
    friend class CameraClient;

    ClientHandler();
    ClientHandler(const ClientHandler&);

    int server_socket_;

    static const char HELLO[];
};

#endif