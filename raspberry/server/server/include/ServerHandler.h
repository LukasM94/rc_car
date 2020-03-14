#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H

#include <netinet/in.h> 
#include <Socket.h>
#include <WorkingThread.h>

class GamePad;
class XboxControllerService;
class CameraService;

class ServerHandler : public Socket, public WorkingThread
{
  public:
    ServerHandler(unsigned int port, GamePad* gamepad, const char* name);
    ~ServerHandler();

    inline static void* runWrapper(void* arg)
    {
      reinterpret_cast<ServerHandler*>(arg)->run();
      return 0;
    }
    virtual void run();

    virtual int initSocket();
    virtual int receive();
    virtual int transmit();
    int listenAndAccept();

  private:
    friend class XboxControllerService;
    friend class CameraService;

    ServerHandler();
    ServerHandler(const ServerHandler&);

    int socket_;
    int client_socket_;

    GamePad* gamepad_;
};

#endif