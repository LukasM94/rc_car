#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <Socket.h>
#include <WorkingThread.h>

class CameraClient;
class GamePadClient;

class ClientHandler : public WorkingThread, public Socket 
{
  public:
    ~ClientHandler();

    static ClientHandler* instance(unsigned int server_port, const char* server_ip);
    static ClientHandler* instance();

    virtual void run();

    virtual int initSocket();
    virtual int receive();
    virtual int transmit();
    virtual int closeSocket();

    int connectToServer();

  private:
    friend class GamePadClient;
    friend class CameraClient;

    ClientHandler(unsigned int server_port, const char* server_ip);
    ClientHandler();
    ClientHandler(const ClientHandler&);

    static ClientHandler* instance_;

    int server_socket_;

    static const char HELLO[];

    GamePadClient* gp_client_;
    CameraClient*  cam_client_;
};

#endif