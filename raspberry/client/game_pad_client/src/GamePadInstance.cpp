#include <GamePadInstance.h>
#include <debug.h>

GamePadInstance* GamePadInstance::instance_ = 0;

GamePadInstance::GamePadInstance() :
  game_pad_()
{
  debug(GP_INSTANCE, "ctor\n");
}

GamePadInstance* GamePadInstance::instance()
{
  debug(GP_INSTANCE, "instance\n");
  if (instance_ == 0)
  {
    instance_ = new GamePadInstance();
  }
  return instance_;
}

GamePadInstance::~GamePadInstance()
{
  debug(GP_INSTANCE, "dtor\n");
}

GamePad* GamePadInstance::getGamePad()
{
  debug(GP_INSTANCE, "getGamePad: gp_clients <%d>, ucontroller <%d>\n", active_game_pad_client_.load(), active_u_controller_.load());
  return &game_pad_;
}