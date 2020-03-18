
#include <GamePadInstance.h>
#include <GamePad.h>
#include <debug.h>
#include <assert.h>

GamePadInstance* GamePadInstance::instance_ = 0;

GamePadInstance::GamePadInstance() :
  game_pad_(0)
{
  debug(GP_INSTANCE, "ctor\n");
}

GamePadInstance::~GamePadInstance()
{
  debug(GP_INSTANCE, "dtor\n");
}

GamePadInstance* GamePadInstance::instance()
{
  if (instance_ == 0)
  {
    instance_ = new GamePadInstance();
  }
  return instance_;
}

GamePad* GamePadInstance::getGamePad()
{
  if (game_pad_ == 0)
  {
    debug(ERROR, "GamePadInstance::getGamePad: game pad is not instantiated\n");
    assert(0);
  }
  return game_pad_;
}

void GamePadInstance::setGamePad(GamePad* const game_pad)
{
  if (game_pad_ != 0)
  {
    debug(ERROR, "GamePadInstance::setGamePad: game pad is already instantiated\n");
    assert(0);
  }
  game_pad_ = game_pad;
}