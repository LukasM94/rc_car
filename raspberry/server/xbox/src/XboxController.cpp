#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <XboxController.h>
#include <debug.h>
#include <string>
#include <GamePad.h>

const char XboxController::DEFAULT_PATH[] = "/dev/input/js0";

//-------------------------------------------------
XboxController::XboxController() :
  WorkingThread("XboxController"),
  path_(DEFAULT_PATH),
  fd_(-1),
  gamepad_(new GamePad(BUTTON_COUNT))
{
  debug(XBOX_CONTR, "ctor: Default path <%s>\n", path_);
}

//-------------------------------------------------
XboxController::XboxController(const char* path) :
  WorkingThread("XboxController"),
  path_(path),
  fd_(-1),
  gamepad_(new GamePad(BUTTON_COUNT))
{
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
  fd_ = open(path_, O_RDONLY);
  int ret;
  while (running_ && (ret = readEvent()) >= 0)
  {
  }
  debug(XBOX_CONTR, "run: Ret is %d\n", ret);
  gamepad_->reset();
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

  bytes = read(fd_, &event_, sizeof(struct js_event));

  int ret = -1;
  if (bytes == sizeof(event_))
  {
    gamepad_->lock();
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
    gamepad_->unlock();
  }
  return ret;
}

//-------------------------------------------------
int XboxController::refreshButton()
{
  return gamepad_->setButton(event_.number, event_.value);
}

//-------------------------------------------------
int XboxController::refreshJoystick()
{
  switch (event_.number)
  {
    case AXIS_L_X:
      gamepad_->setLeftAxisX(event_.value >> 8);
      // gamepad_->left_.x_ = (event_.value >> 8);
      break;
    case AXIS_L_Y:
      gamepad_->setLeftAxisY(event_.value >> 8);
      // gamepad_->left_.y_ = (event_.value >> 8);
      break;
    case AXIS_R_X:
      gamepad_->setRightAxisX(event_.value >> 8);
      // gamepad_->right_.x_ = (event_.value >> 8);
      break;
    case AXIS_R_Y:
      gamepad_->setRightAxisY(event_.value >> 8);
      // gamepad_->right_.y_ = (event_.value >> 8);
      break;
    case BUTTON_LT:
      gamepad_->setLTButton((event_.value >> 8) > LT_THRESHOLD);
      // gamepad_->lt_ = ((event_.value >> 8) > LT_THRESHOLD);
      break;
    case BUTTON_RT:
      gamepad_->setRTButton((event_.value >> 8) > RT_THRESHOLD);
      // gamepad_->rt_ = ((event_.value >> 8) > RT_THRESHOLD);
      break;
    default:
      return 3;
  }
  return 0;
}
