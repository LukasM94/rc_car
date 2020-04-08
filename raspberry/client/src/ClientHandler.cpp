
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
#include <CameraClient.h>
#include <ThreadHandler.h>
#include <client_config.h>

const char ClientHandler::HELLO[] = "Hello from client";

//-------------------------------------------------
ClientHandler::ClientHandler(unsigned int server_port, const char* server_ip) :
  Socket(server_port, server_ip),
  WorkingThread("ClientHandler"),
  gp_client_(0),
  cam_client_(0)
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
    debug(WARNING, "ClientHandler::init: Socket creation error \n"); 
    return -1; 
  } 
  
  address_.sin_family = AF_INET; 
  address_.sin_port = htons(port_); 
    
  if(inet_pton(AF_INET, ip_address_.c_str(), &address_.sin_addr)<=0)  
  { 
    debug(WARNING, "ClientHandler::init: Invalid address/ Address not supported \n"); 
    return -1; 
  } 
  return 0;
}

//-------------------------------------------------
int ClientHandler::receive()
{
  memset(input_buffer_, 0, BUFFER_SIZE);
  int ret;
  ret = recv(server_socket_ , input_buffer_, BUFFER_SIZE, MSG_NOSIGNAL | MSG_WAITALL); 
  if (ret <= 0)
  {
    debug(WARNING, "ClientHandler::receive: Quit connection with ret %d\n", ret);
    connected_ = 0;
  }
  else
  {
    debug(CLIENT_DATA, "receive: Got message with length %d\n", ret);
  }
  return ret;
}

//-------------------------------------------------
int ClientHandler::transmit()
{
  int ret;
  // debug(CLIENT_HAND, "transmit: Want to send message\n");

  ret = send(server_socket_, output_buffer_, BUFFER_SIZE, MSG_NOSIGNAL); 
  if (ret < 0)
  {
    debug(WARNING, "ClientHandler::transmit: Quit connection with ret %d\n", ret); 
    connected_ = 0;
  }
  else
  {
    debug(CLIENT_DATA, "transmit: Successfully sent data to client\n"); 
  }
  return ret;
}

//-------------------------------------------------
int ClientHandler::connectToServer()
{
  debug(CLIENT_HAND, "transmit: Wait for connection\n"); 
  if (connect(server_socket_, (struct sockaddr*)&address_, sizeof(address_)) == -1) 
  { 
    debug(WARNING, "ClientHandler::connectToServer: Connection failed\n"); 
    return 1; 
  } 
  return 0;
}

//-------------------------------------------------
void ClientHandler::run()
{
  int ret = 0;

  gp_client_  = new GamePadClient(this);
  cam_client_ = new CameraClient(this);

  debug(CLIENT_HAND, "run: Start\n");
  while (running_)
  {
    if (initSocket())
    {
      break;
    }
    debug(CLIENT_HAND, "run: Successfully initialized\n");

    if ((ret = connectToServer()) < 0)
    {
      break;
    }
    else if (ret > 0)
    {
      debug(CLIENT_HAND, "run: Wait %d sec and try again\n", SLEEP_TIME_TRY_AGAIN);
      sleep(SLEEP_TIME_TRY_AGAIN);
      continue;
    }

    debug(CLIENT_HAND, "run: Connected\n");
    connected_ = 1;

    ThreadHandler::lock();
    // game pad client is essential
    ThreadHandler::beginThread(gp_client_, 0);
    // camera client is not
    // raspberry has to reboot if you plug and unplug the camera!!!
    ThreadHandler::startExternThread(cam_client_);
    ThreadHandler::unlock();

    while (connected_)
    {
      debug(CLIENT_HAND, "run: Go to sleep\n");
      ThreadHandler::gotoSleep();
      debug(CLIENT_HAND, "run: Got up\n");
      sleep(CLIENT_SLEEP_TIME);
    }

    closeSocket();

    ThreadHandler::waitTillThreadFinished(gp_client_);
    ThreadHandler::waitTillThreadFinished(cam_client_);
    ThreadHandler::exitThread(gp_client_);
    // ThreadHandler::exitThread(cam_client_);
  }

  delete gp_client_;
  delete cam_client_;

  debug(CLIENT_HAND, "run: Exit\n");
}

//-------------------------------------------------
int ClientHandler::closeSocket()
{
  return close(server_socket_);
}