
#include <ServerHandler.h>
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <string.h> 
#include <debug.h>
#include <GamePad.h>
#include <exception>
#include <config.h>
#include <XboxControllerService.h>
#include <CameraService.h>
#include <ThreadHandler.h>
#include <assert.h>
#include <TransceivedDataInstance.h>

#define HELLO "Hello from server"

//-------------------------------------------------
ServerHandler::ServerHandler(unsigned int port) : 
  WorkingThread("ServerHandler"),
  Socket(port, "127.0.0.1"),
  xc_service_(0),
  camera_service_(0)
{
  debug(SERVER_HAND, "ctor:\n");
}

//-------------------------------------------------
ServerHandler::~ServerHandler()
{
  debug(SERVER_HAND, "dtor:\n");
}

//-------------------------------------------------
void ServerHandler::run()
{
  int ret = 0;

  xc_service_     = new XboxControllerService(this);
  camera_service_ = new CameraService(this);

  debug(SERVER_HAND, "run: Start\n");
  if (initSocket())
  {
    assert(0);
  }
  debug(SERVER_HAND, "run: Successfully initialized and binded\n");

  while (running_)
  {
    if ((ret = listenAndAccept()) < 0)
    {
      break;
    }
    else if (ret > 0)
    {
      debug(SERVER_HAND, "run: Wait 2 sec and try again\n");
      sleep(2);
      continue;
    }
    debug(SERVER_HAND, "run: Connected\n");
    connected_ = 1;

    ThreadHandler::lock();
    ThreadHandler::beginThread(xc_service_, 0);
    ThreadHandler::beginThread(camera_service_, 0);
    ThreadHandler::unlock();

    while (connected_)
    {
      sleep(5);
      debug(SERVER_HAND, "run: Go to sleep\n");
      ThreadHandler::gotoSleep();
      debug(SERVER_HAND, "run: Got up\n");
    }

    closeSocket();

    ThreadHandler::waitTillThreadFinished(xc_service_);
    ThreadHandler::waitTillThreadFinished(camera_service_);
    ThreadHandler::exitThread(xc_service_);
    ThreadHandler::exitThread(camera_service_);

  }

  delete xc_service_;
  delete camera_service_;
  
  debug(SERVER_HAND, "run: Exit with ret %d\n", ret);
}

//-------------------------------------------------
int ServerHandler::initSocket()
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
int ServerHandler::receive()
{
  memset(input_buffer_, 0, BUFFER_SIZE);
  int ret;
  ret = recv(client_socket_, input_buffer_, BUFFER_SIZE, MSG_NOSIGNAL | MSG_WAITALL); 
  if (ret < 0)
  {
    debug(WARNING, "ServerHandler::receive: Quit connection with ret %d\n", ret); 
    connected_ = 0;
  }
  else
  {
    debug(SERVER_DATA, "receive: Got message with length %d\n", ret);
    // debug(SERVER_DATA, "receive: msg <%s>\n", input_buffer_); 
  }
  return 0;
}

//-------------------------------------------------
int ServerHandler::transmit()
{
  int ret;
  // debug(SERVER_HAND, "transmit: Want to send message\n");

  ret = send(client_socket_, output_buffer_, BUFFER_SIZE, MSG_NOSIGNAL); 
  if (ret < 0)
  {
    debug(SERVER_HAND, "transmit: Quit connection with ret %d\n", ret); 
    connected_ = 0;
  }
  else
  {
    // debug(SERVER_HAND, "transmit: Successfully sent data to client\n"); 
  }
  return 0;
}

//-------------------------------------------------
int ServerHandler::listenAndAccept()
{
  int addrlen = sizeof(address_); 

  if (listen(socket_, 3) < 0) 
  { 
    debug(ERROR, "server::listenAndAccept: Listen\n"); 
    return -1; 
  } 

  debug(SERVER_HAND, "listenAndAccept: Wait at acceptence\n"); 
  if ((client_socket_ = accept(socket_, (struct sockaddr *)&address_,  
             (socklen_t*)&addrlen)) < 0) 
  { 
    debug(WARNING, "server::listenAndAccept: Accept\n"); 
    return 1; 
  } 
  return 0;
}

//-------------------------------------------------
int ServerHandler::closeSocket()
{
  return close(client_socket_);
}

//-------------------------------------------------
int ServerHandler::closeServerSocket()
{
  return close(socket_);
}