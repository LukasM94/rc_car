#ifndef SOCKET_H
#define SOCKET_H

#include <atomic>
#include <netinet/in.h> 
#include <string>
#include <config.h>

class Socket
{
  public:
    Socket(unsigned int port, const char* ip_address);
    ~Socket();
    virtual int initSocket() = 0;
    virtual int transmit() = 0;
    virtual int receive() = 0;;
    virtual int closeSocket() = 0;

  protected:
    Socket();
    Socket(const Socket&);

    static const int BUFFER_SIZE = COMMON_PACKAGE_SIZE;

    char output_buffer_[BUFFER_SIZE];
    char input_buffer_[BUFFER_SIZE];
    int  port_;

    std::string ip_address_;

	  struct sockaddr_in address_; 
    std::atomic_bool   connected_;
};

#endif