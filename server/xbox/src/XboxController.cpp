#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <XboxController.h>
#include <debug.h>
#include <string>
#include <GamePad.h>
#include <GamePadInstance.h>

const char XboxController::DEFAULT_PATH[] = "/dev/input/js0";

//-------------------------------------------------
XboxController::XboxController() :
  WorkingThread("XboxController"),
  path_(DEFAULT_PATH),
  fd_(-1)
{
  GamePadInstance::instance()->setGamePad(new GamePad(BUTTON_COUNT));
  debug(XBOX_CONTR, "ctor: Default path <%s>\n", path_);
}

//-------------------------------------------------
XboxController::XboxController(const char* path) :
  WorkingThread("XboxController"),
  path_(path),
  fd_(-1)
{
  GamePadInstance::instance()->setGamePad(new GamePad(BUTTON_COUNT));
  debug(XBOX_CONTR, "ctor: Path <%s>\n", path_);
}

//-------------------------------------------------
XboxController::~XboxController()
{
  debug(XBOX_CONTR, "dtor\n");
}

//-------------------------------------------------
void XboxController::run()
{
  debug(XBOX_CONTR, "run: Start\n");
  GamePad* game_pad = GamePadInstance::instance()->getGamePad();
  game_pad->setConnected();
  fd_ = open(path_, O_RDONLY);
  int ret;
  while (running_ && (ret = readEvent()) >= 0)
  {
  }
  debug(XBOX_CONTR, "run: Ret is %d\n", ret);
  game_pad->setUnconnected();
  game_pad->reset();
  close(fd_);
  debug(XBOX_CONTR, "run: Exit\n");
}

//-------------------------------------------------
void XboxController::print()
{
  // TODO
}

//-------------------------------------------------
int XboxController::readEvent()
{
  ssize_t bytes;

  GamePad* game_pad = GamePadInstance::instance()->getGamePad();

  bytes = read(fd_, &event_, sizeof(struct js_event));

  int ret = -1;
  if (bytes == sizeof(event_))
  {
    game_pad->lock();
    if (isButton())
    {
      ret = refreshButton();
    }
    else if (isJoyStick())
    {
      ret = refreshJoystick();
    }
    else
    {
      ret = event_.type;
    }
    game_pad->unlock();
  }
  return ret;
}

//-------------------------------------------------
int XboxController::refreshButton()
{
  GamePad* game_pad = GamePadInstance::instance()->getGamePad();
  return game_pad->setButton(event_.number, event_.value);
}

//-------------------------------------------------
int XboxController::refreshJoystick()
{
  GamePad* game_pad = GamePadInstance::instance()->getGamePad();
  switch (event_.number)
  {
    case AXIS_L_X:
      game_pad->setLeftAxisX(event_.value >> 8);
      // game_pad->left_.x_ = (event_.value >> 8);
      break;
    case AXIS_L_Y:
      game_pad->setLeftAxisY(event_.value >> 8);
      // game_pad->left_.y_ = (event_.value >> 8);
      break;
    case AXIS_R_X:
      game_pad->setRightAxisX(event_.value >> 8);
      // game_pad->right_.x_ = (event_.value >> 8);
      break;
    case AXIS_R_Y:
      game_pad->setRightAxisY(event_.value >> 8);
      // game_pad->right_.y_ = (event_.value >> 8);
      break;
    case BUTTON_LT:
      game_pad->setLTButton((event_.value >> 8) > LT_THRESHOLD);
      // game_pad->lt_ = ((event_.value >> 8) > LT_THRESHOLD);
      break;
    case BUTTON_RT:
      game_pad->setRTButton((event_.value >> 8) > RT_THRESHOLD);
      // game_pad->rt_ = ((event_.value >> 8) > RT_THRESHOLD);
      break;
    default:
      return 3;
  }
  return 0;
}
