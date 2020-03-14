
#include <XboxControllerService.h>
#include <ServerHandler.h>
#include <debug.h>
#include <GamePad.h>
#include <string.h>
#include <unistd.h>
#include <config.h>

XboxControllerService::XboxControllerService(ServerHandler* server_handler, GamePad* gamepad) :
  WorkingThread("XboxControllerService"),
  server_handler_(server_handler),
  gamepad_(gamepad)
{
  debug(XB_SERVICE, "ctor: server_handler <%p>, gamepad <%p>\n", server_handler, gamepad);
}

XboxControllerService::~XboxControllerService()
{
  debug(XB_SERVICE, "dtor\n");
}

void XboxControllerService::run()
{
  debug(XB_SERVICE, "run: Start\n");
  while (server_handler_->connected_)
  {
    usleep(SERVER_SEND_DATA);
    memset(server_handler_->output_buffer_, 0, server_handler_->BUFFER_SIZE);
    gamepad_->getMsg(server_handler_->output_buffer_, server_handler_->BUFFER_SIZE);
    server_handler_->transmit();
  }
  debug(XB_SERVICE, "run: Exit\n");
}