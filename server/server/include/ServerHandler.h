#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H

#include <netinet/in.h> 
#include <Socket.h>
#include <WorkingThread.h>

class XboxControllerService;
class CameraService;

class ServerHandler : public WorkingThread, public Socket
{
  public:
    ~ServerHandler();

    static ServerHandler* instance(unsigned int port);
    static ServerHandler* instance();

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

    ServerHandler(unsigned int port);
    ServerHandler();
    ServerHandler(const ServerHandler&);

    static ServerHandler* instance_;

    int socket_;
    int client_socket_;

    XboxControllerService* xc_service_;
    CameraService*         camera_service_;
};

#endif