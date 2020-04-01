
#include <Socket.h>
#include <string.h> 
#include <debug.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 

//-------------------------------------------------
Socket::Socket(unsigned int port, const char* ip_address) :
  port_(port),
  ip_address_(ip_address),
  address_({}),
  connected_(1)
{

}

//-------------------------------------------------
Socket::~Socket()
{

}
