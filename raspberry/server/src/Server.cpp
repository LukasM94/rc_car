
#include <Server.h>
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <string.h> 
#include <debug.h>
#include <GamePad.h>
#include <exception>

#define HELLO "Hello from server"

//-------------------------------------------------
Server::Server(unsigned int port, GamePad* gamepad) : 
	Socket(port, "127.0.0.1"),
  gamepad_(gamepad),
	running_(1)
{
  debug(SERVER, "ctor:\n");
}

//-------------------------------------------------
Server::~Server()
{
  debug(SERVER, "dtor:\n");
}

//-------------------------------------------------
void Server::run()
{
	int ret = 0;

  debug(SERVER, "run: Start\n");
  if (init())
  {
    exit(-1);
  }
  debug(SERVER, "run: Successfully initialized and binded\n");

  while (running_)
  {
    if ((ret = listenAndAccept()) < 0)
    {
      break;
    }
		else if (ret > 0)
		{
  		debug(SERVER, "run: Wait 2 sec and try again\n");
			sleep(2);
			continue;
		}
		receive();
		connected_ = 1;
		while (connected_)
		{
			usleep(100000);
			memset(buffer_, 0, BUFFER_SIZE);
			gamepad_->getMsg(buffer_, BUFFER_SIZE);
			transmit();
		}
  }
  debug(SERVER, "run: Exit with ret %d\n", ret);
}

//-------------------------------------------------
int Server::init()
{
	int opt = 1; 

	// Creating socket file descriptor 
	if ((socket_ = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		debug(ERROR, "server::init: Socket failed\n"); 
		return -1; 
	} 
	   
	// Forcefully attaching socket to the port 
	if (setsockopt(socket_, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
												  &opt, sizeof(opt))) 
	{ 
		debug(ERROR, "server::init: Setsockopt\n"); 
		return -2; 
	} 
	
	address_.sin_family      = AF_INET; 
	address_.sin_addr.s_addr = INADDR_ANY; 
	address_.sin_port        = htons(port_); 
	   
	// Forcefully attaching socket to the port 
	if (bind(socket_, (struct sockaddr*)&address_,  
								 sizeof(address_)) < 0) 
	{ 
		debug(ERROR, "server::bindServer: Bind failed\n"); 
		return -1; 
	} 
  return 0;
}

//-------------------------------------------------
int Server::receive()
{
  memset(buffer_, 0, BUFFER_SIZE);
	int ret;
	ret = recv(client_socket_, buffer_, BUFFER_SIZE - 1, MSG_DONTWAIT | MSG_NOSIGNAL); 
	if (ret < 0)
	{
		debug(SERVER, "receive: Quit connection with ret %d\n", ret); 
		connected_ = 0;
	}
	else
	{
		debug(SERVER, "receive: Got message with length %d\n", ret);
		debug(SERVER_DATA, "receive: msg <%s>\n", buffer_); 
	}
	return ret;
}

//-------------------------------------------------
int Server::transmit()
{
	int ret;
	// debug(SERVER, "transmit: Want to send message\n");

	ret = send(client_socket_, buffer_, sizeof(buffer_), MSG_NOSIGNAL); 
	if (ret < 0)
	{
		debug(SERVER, "transmit: Quit connection with ret %d\n", ret); 
		connected_ = 0;
	}
	else
	{
		// debug(SERVER, "transmit: Successfully sent data to client\n"); 
	}
	return ret;
}

//-------------------------------------------------
int Server::listenAndAccept()
{
	int addrlen = sizeof(address_); 

  if (listen(socket_, 3) < 0) 
	{ 
		debug(ERROR, "server::listenAndAccept: Listen\n"); 
		return -1; 
	} 

	debug(SERVER, "listenAndAccept: Wait at acceptence\n"); 
	if ((client_socket_ = accept(socket_, (struct sockaddr *)&address_,  
					   (socklen_t*)&addrlen)) < 0) 
	{ 
		debug(WARNING, "server::listenAndAccept: Accept\n"); 
		return 1; 
	} 
  return 0;
}
