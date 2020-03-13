
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <string> 
#include <algorithm> 
#include <ClientHandler.h>
#include <config.h>
#include <debug.h>
#include <GamePadClient.h>
  
const char ClientHandler::HELLO[] = "Hello from client";

//-------------------------------------------------
ClientHandler::ClientHandler(unsigned int server_port, const char* server_ip) :
	Socket(server_port, server_ip),
  WorkingThread("ClientHandler")
{
  debug(CLIENT_HAND, "ctor: %d, %s\n", server_port, server_ip);
}

//-------------------------------------------------
ClientHandler::~ClientHandler()
{
  debug(CLIENT_HAND, "dtor:\n");
}

//-------------------------------------------------
int ClientHandler::initSocket()
{
  int valread = 0; 

  if ((server_socket_ = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
  { 
    debug(ERROR, "ClientHandler::init: Socket creation error \n"); 
    return -1; 
  } 
  
  address_.sin_family = AF_INET; 
  address_.sin_port = htons(port_); 
    
  if(inet_pton(AF_INET, ip_address_.c_str(), &address_.sin_addr)<=0)  
  { 
    debug(ERROR, "ClientHandler::init: Invalid address/ Address not supported \n"); 
    return -1; 
  } 
  return 0;
}

//-------------------------------------------------
int ClientHandler::receive()
{
  memset(buffer_, 0, BUFFER_SIZE);
	int ret;
	ret = read(server_socket_ , buffer_, BUFFER_SIZE); 
	if (ret <= 0)
	{
		debug(CLIENT_HAND, "receive: Quit connection with ret %d\n", ret);
		connected_ = 0;
	}
	else
	{
		debug(CLIENT_DATA, "receive: Got message with length %d\n", ret);
    std::string str(buffer_, BUFFER_SIZE);
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
    str.erase(std::remove(str.begin(), str.end(), '\t'), str.end());
    str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    str.erase(std::remove(str.begin(), str.end(), 0), str.end());
		debug(CLIENT_DATA, "receive: msg %s\n", str.c_str()); 
	}
	return ret;
}

//-------------------------------------------------
int ClientHandler::transmit()
{
  int ret;
	debug(CLIENT_HAND, "transmit: Want to send message\n");

	ret = send(server_socket_, buffer_, sizeof(buffer_), MSG_NOSIGNAL); 
	if (ret < 0)
	{
		debug(CLIENT_HAND, "transmit: Quit connection with ret %d\n", ret); 
		connected_ = 0;
	}
	else
	{
		debug(CLIENT_HAND, "transmit: Successfully sent data to client\n"); 
	}
	return ret;
}

//-------------------------------------------------
int ClientHandler::connectToServer()
{
  if (connect(server_socket_, (struct sockaddr*)&address_, sizeof(address_)) < 0) 
  { 
    debug(WARNING, "ClientHandler::connectToServer: Connection Failed \n"); 
    return 1; 
  } 
  return 0;
}

//-------------------------------------------------
void ClientHandler::run()
{
  int ret = 0;

  debug(CLIENT_HAND, "run: Start\n");
  while (running_)
  {
    if (initSocket())
    {
      exit(-1);
    }
    debug(CLIENT_HAND, "run: Successfully initialized\n");

    if ((ret = connectToServer()) < 0)
    {
      break;
    }
    else if (ret > 0)
    {
      debug(CLIENT_HAND, "run: Wait 2 sec and try again\n");
      sleep(2);
      continue;
    }

    debug(CLIENT_HAND, "run: Connected\n");

    connected_ = 1;
    pthread_t tid_gp_client;

    GamePadClient* gp_client  = new GamePadClient(this);

    pthread_create(&tid_gp_client, 0, GamePadClient::runWrapper, gp_client);

    while (connected_)
    {
      debug(CLIENT_HAND, "run: Nothing to do\n");
      sleep(5);
    }

    pthread_cancel(tid_gp_client);
    pthread_join(tid_gp_client, 0);
  }
  debug(CLIENT_HAND, "run: Exit\n");
}
