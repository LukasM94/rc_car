
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <string> 
#include <algorithm> 
#include <GamePadClient.h>
#include <config.h>
#include <debug.h>
#include <GamePad.h>
  
const char GamePadClient::HELLO[] = "Hello from client";

//-------------------------------------------------
GamePadClient::GamePadClient(unsigned int server_port, const char* server_ip):
	Socket(server_port, server_ip),
  game_pad_(0),
  running_(1)
{
  debug(GP_CLIENT, "ctor: %d, %s\n", server_port, server_ip);
}

//-------------------------------------------------
GamePadClient::~GamePadClient()
{
  if (game_pad_ != 0)
  {
    delete game_pad_;
  }
  debug(GP_CLIENT, "dtor:\n");
}

//-------------------------------------------------
int GamePadClient::init()
{
  int valread = 0; 

  if ((server_socket_ = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
  { 
    debug(ERROR, "GamePadClient::init: Socket creation error \n"); 
    return -1; 
  } 
  
  address_.sin_family = AF_INET; 
  address_.sin_port = htons(port_); 
    
  if(inet_pton(AF_INET, ip_address_.c_str(), &address_.sin_addr)<=0)  
  { 
    debug(ERROR, "GamePadClient::init: Invalid address/ Address not supported \n"); 
    return -1; 
  } 
  return 0;
}

//-------------------------------------------------
int GamePadClient::receive()
{
  memset(buffer_, 0, BUFFER_SIZE);
	int ret;
	ret = read(server_socket_ , buffer_, BUFFER_SIZE); 
	if (ret <= 0)
	{
		debug(GP_CLIENT, "receive: Quit connection with ret %d\n", ret);
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
int GamePadClient::transmit()
{
  int ret;
	debug(GP_CLIENT, "transmit: Want to send message\n");

	ret = send(server_socket_, buffer_, sizeof(buffer_), MSG_NOSIGNAL); 
	if (ret < 0)
	{
		debug(GP_CLIENT, "transmit: Quit connection with ret %d\n", ret); 
		connected_ = 0;
	}
	else
	{
		debug(GP_CLIENT, "transmit: Successfully sent data to client\n"); 
	}
	return ret;
}

//-------------------------------------------------
int GamePadClient::connectToServer()
{
  if (connect(server_socket_, (struct sockaddr*)&address_, sizeof(address_)) < 0) 
  { 
    debug(WARNING, "GamePadClient::connectToServer: Connection Failed \n"); 
    return 1; 
  } 
  return 0;
}

//-------------------------------------------------
void GamePadClient::run()
{
  int ret = 0;

  debug(GP_CLIENT, "run: Start\n");
  while (running_)
  {
    if (init())
    {
      exit(-1);
    }
    debug(GP_CLIENT, "run: Successfully initialized\n");

    if ((ret = connectToServer()) < 0)
    {
      break;
    }
    else if (ret > 0)
    {
      debug(GP_CLIENT, "run: Wait 2 sec and try again\n");
      sleep(2);
      continue;
    }
    connected_ = 1;
    memset(buffer_, 0, BUFFER_SIZE);
    strncpy(buffer_, HELLO, BUFFER_SIZE - 1);
    buffer_[BUFFER_SIZE - 1] = 0;
    transmit();
    debug(GP_CLIENT, "run: Connected\n");
    while (connected_)
    {
      ret = receive();
      std::string str(buffer_, BUFFER_SIZE);
      str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
      str.erase(std::remove(str.begin(), str.end(), '\t'), str.end());
      str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
      str.erase(std::remove(str.begin(), str.end(), 0), str.end());
      debug(GP_CLIENT_D, "run: string is %s\n", str.c_str());
      game_pad_ = GamePad::getFromString(game_pad_, str.c_str());
    }
  }
  debug(GP_CLIENT, "run: Exit\n");
}
