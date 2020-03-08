
#include <GamePad.h>
#include <string>
#include <algorithm>
#include <string>
#include <string.h>
#include <debug.h>
#if defined(__x86_64)
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#else // if defined(__arm__)
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#include <jsoncpp/json/value.h>
#endif
#include <iostream>

GamePad::GamePad() :
  lt_(0),
  rt_(0),
  buttons_count_(0),
  buttons_(0)
{
  initLock();
  debug(GAME_PAD, "ctor\n");
}


GamePad::GamePad(uint8_t button_count) :
  lt_(0),
  rt_(0),
  buttons_count_(button_count),
  buttons_(new std::atomic_bool[buttons_count_])
{
  initLock();
  debug(GAME_PAD, "ctor: button_count <%d>\n", button_count);
}

GamePad::~GamePad()
{
  debug(GAME_PAD, "dtor\n");
  delete buttons_;
}

const char GamePad::STRING_LEFT[]  = "left";
const char GamePad::STRING_RIGHT[] = "right";
const char GamePad::STRING_LT[]    = "lt";
const char GamePad::STRING_RT[]    = "rt";
const char GamePad::STRING_BCNT[]  = "bcnt";
const char GamePad::STRING_BTN[]   = "bnt";

int GamePad::getFromString(GamePad* game_pad, const char* str)
{
  debug(GAME_PAD, "getFromString\n");

  try
  {
    game_pad->lock();
    Json::Value  root;
    Json::Reader reader;
    Json::Value  left;
    Json::Value  right;
    Json::Value  buttons;

    int ret = reader.parse(str, root);
    if (ret == 0)
    {
      debug(WARNING, "GamePad::getMsg: parsing not successful\n");
      game_pad->unlock();
      return -1;
    }

    buttons = root[STRING_BTN];
    left    = root[STRING_LEFT];
    right   = root[STRING_RIGHT];

    unsigned int button_cnt = buttons.size();

    if (game_pad->getButtonCnt() != button_cnt)
    {
      game_pad->allocateButtons(button_cnt);
    }

    game_pad->left_.x_  = left[0].asInt();  
    game_pad->left_.y_  = left[1].asInt();  
    game_pad->right_.x_ = right[0].asInt();  
    game_pad->right_.y_ = right[1].asInt();  

    game_pad->rt_ = root[STRING_RT].asBool();
    game_pad->lt_ = root[STRING_LT].asBool();

    for (int i = 0; i < button_cnt; ++i)
    {
      game_pad->buttons_[i] = buttons[i].asBool();
    }

    game_pad->unlock();
    return 0;
  }
  catch (std::string const& msg)
  {
    debug(WARNING, "GamePad::getFromString: %s\n", msg.c_str());
    return -1;
  }
}

int GamePad::getMsg(char* msg, unsigned int max_length)
{
  debug(GAME_PAD, "getMsg\n");

  int ret;
  Json::Value root;
  if ((ret = getJson(root)) != 0)
  {
    return ret;
  }

  unsigned int length = root.toStyledString().length();
  if (length > max_length)
  {
    return -1;
  }

  memcpy(msg, root.toStyledString().c_str(), length);
  return 0;
}

int GamePad::getJson(Json::Value& root)
{
  try
  {
    Json::Value left;
    Json::Value right;
    Json::Value buttons;

    left[0]  = left_.x_.load();
    left[1]  = left_.y_.load();
    right[0] = right_.x_.load();
    right[1] = right_.y_.load();

    root[STRING_LEFT]  = left;
    root[STRING_RIGHT] = right;
    root[STRING_LT]    = lt_.load()? 1 : 0;
    root[STRING_RT]    = rt_.load()? 1 : 0;

    for (int i = 0; i < buttons_count_; ++i)
    {
      buttons[i] = buttons_[i].load()? 1 : 0;
    }
    root[STRING_BTN] = buttons;
    return 0;
  }
  catch (std::string const& msg)
  {
    debug(WARNING, "GamePad::getjson: %s\n", msg.c_str());
    return -1;
  }
}

int GamePad::getMsg(char** msg, unsigned int* length)
{
  debug(GAME_PAD, "getMsg: Start\n");

  int ret;
  Json::Value root;
  if ((ret = getJson(root)) != 0)
  {
    return ret;
  }

  *length = root.toStyledString().length();
  *msg    = new char[*length];
  memcpy(*msg, root.toStyledString().c_str(), *length);

  if (OUTPUT_ENABLED & OUTPUT_ENABLED)
  {
    std::string temp = root.toStyledString();
    temp.erase(std::remove(temp.begin(), temp.end(), '\n'), temp.end());
    temp.erase(std::remove(temp.begin(), temp.end(), '\t'), temp.end());
    debug(GAME_PAD, "GamePad::getjson: %s\n", temp.c_str());
  }
  return 0;
}

void GamePad::allocateButtons(unsigned int button_ctn)
{
  if (buttons_ != 0)
  {
    delete buttons_;
  }
  buttons_ = new std::atomic_bool[button_ctn]; 
  buttons_count_ = button_ctn;
}

void GamePad::reset()
{
  debug(GAME_PAD, "reset: Reset all data for left, right, lt, rt and %d buttons\n", buttons_count_.load());
  left_.x_  = 0;
  left_.y_  = 0;
  right_.x_ = 0;
  right_.y_ = 0;

  lt_ = 0;
  rt_ = 0;

  for (int i = 0; i < buttons_count_; ++i)
  {
    buttons_[i] = 0;
  }
}