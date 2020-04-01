
#include <string.h> 
#include <string> 
#include <algorithm> 
#include <GamePadClient.h>
#include <debug.h>
#include <GamePadInstance.h>
#include <ClientHandler.h>
  
//-------------------------------------------------
GamePadClient::GamePadClient(ClientHandler* client_handler) :
  WorkingThread("GamePadClient"),
  client_handler_(client_handler)
{
  debug(GP_CLIENT, "ctor: %p\n", client_handler);
}

//-------------------------------------------------
GamePadClient::~GamePadClient()
{
  debug(GP_CLIENT, "dtor:\n");
}

//-------------------------------------------------
void GamePadClient::run()
{
  int ret = 0;
  unsigned int not_successful = 0;

  debug(GP_CLIENT, "run: Start\n");

  GamePadInstance::instance()->startGamePadClient();
  while (client_handler_->connected_)
  {
    ret = client_handler_->receive();
    std::string str(client_handler_->input_buffer_, client_handler_->BUFFER_SIZE);
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
    str.erase(std::remove(str.begin(), str.end(), '\t'), str.end());
    str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
    str.erase(std::remove(str.begin(), str.end(), 0), str.end());
    debug(GP_CLIENT_D, "run: string is %s\n", str.c_str());

    if (GamePad::getFromString(GamePadInstance::instance()->getGamePad(), str.c_str()) != 0)
    {
      not_successful++;
      if (not_successful == 10)
      {
        debug(WARNING, "GamePadClient::run: 10 times in a row not successful\n");
        client_handler_->connected_ = 0;
      }
    }
    else
    {
      not_successful = 0;
    }
  }
  GamePadInstance::instance()->exitGamePadClient();

  debug(GP_CLIENT, "run: Exit\n");
}
