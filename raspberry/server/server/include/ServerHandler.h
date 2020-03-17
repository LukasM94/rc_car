#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H

#include <netinet/in.h> 
#include <Socket.h>
#include <WorkingThread.h>

class GamePad;
class XboxControllerService;
class CameraService;

class ServerHandler : public WorkingThread, public Socket
{
  public:
    ServerHandler(unsigned int port, GamePad* gamepad);
    ~ServerHandler();

    virtual void run();

    virtual int initSocket();
    virtual int receive();
    virtual int transmit();
    virtual int closeSocket();
    int closeServerSocket();

    int listenAndAccept();

  private:
    friend class XboxControllerService;
    friend class CameraService;

    ServerHandler();
    ServerHandler(const ServerHandler&);

    int socket_;
    int client_socket_;

    GamePad* gamepad_;

    XboxControllerService* xc_service_;
    CameraService*         camera_service_;
};

#endif