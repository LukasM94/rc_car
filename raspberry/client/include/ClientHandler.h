#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <Socket.h>
#include <WorkingThread.h>
#include <stdint.h>
#include <Lock.h>

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

    void addLatency(size_t latency);
    size_t meanOfLatency();
    ssize_t diffOfLastLatency();
    void lockLatency();
    void unlockLatency();

  private:
    friend class GamePadClient;
    friend class CameraClient;

    ClientHandler(unsigned int server_port, const char* server_ip);
    ClientHandler();
    ClientHandler(const ClientHandler&);

    static ClientHandler* instance_;

    int server_socket_;

    static const char HELLO[];

    Lock latency_lock_;
    int latency_index_;
    ssize_t* latencies_;

    GamePadClient* gp_client_;
    CameraClient*  cam_client_;

    static const unsigned int COUNT_LATENCIES = 1024;
};

#endif
