
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

#define HELLO "Hello from server"

//-------------------------------------------------
ServerHandler::ServerHandler(unsigned int port, GamePad* gamepad, const char* name) : 
  WorkingThread(name),
  Socket(port, "127.0.0.1"),
  gamepad_(gamepad)
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

  debug(SERVER_HAND, "run: Start\n");
  if (initSocket())
  {
    exit(-1);
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

    pthread_t tid_xc_service;
    pthread_t tid_camera_service;

    XboxControllerService* xc_service     = new XboxControllerService(this, gamepad_);
    CameraService*         camera_service = new CameraService(this);

    pthread_create(&tid_xc_service, 0, XboxControllerService::runWrapper, xc_service);	
    pthread_create(&tid_camera_service, 0, CameraService::runWrapper, camera_service);	

    while (connected_)
    {
      debug(SERVER_HAND, "run: Nothing to do\n");
      sleep(5);
    }

    pthread_join(tid_camera_service, 0);
    pthread_join(tid_xc_service, 0);
    
    closeSocket();
  }
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
    debug(SERVER_HAND, "receive: Quit connection with ret %d\n", ret); 
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