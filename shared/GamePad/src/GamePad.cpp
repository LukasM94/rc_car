
#include <GamePad.h>
#include <string>
#include <algorithm>
#include <string>
#include <string.h>
#include <debug.h>
#include <assert.h>
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
#include <assert.h>

GamePad::GamePad() :
  lt_(0),
  rt_(0),
  buttons_count_(0),
  buttons_(0),
  cond_("GamePad::cond_")
{
  debug(GAME_PAD, "ctor\n");
}

GamePad::GamePad(uint8_t button_count) :
  lt_(0),
  rt_(0),
  buttons_count_(button_count),
  buttons_(new std::atomic_bool[buttons_count_]),
  cond_("GamePad::cond_")
{
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
const char GamePad::STRING_CON[]   = "cnt";

int GamePad::getFromString(GamePad* game_pad, const char* str)
{
  debug(GAME_PAD, "getFromString\n");

  game_pad->lock();
  try
  {
    Json::Value  root;
    Json::Reader reader;
    Json::Value  left;
    Json::Value  right;
    Json::Value  buttons;

    int ret = reader.parse(str, root);
    if (ret == 0)
    {
      debug(WARNING, "GamePad::getFromString: parsing not successful\n");
      // for (int i = 0; i < 4096; ++i)
      // {
      //   printf("%c", str[i]);
      // }
      goto GET_FROM_STRING_ERROR;
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

    game_pad->connected_ = root[STRING_CON].asBool();

    for (int i = 0; i < button_cnt; ++i)
    {
      game_pad->buttons_[i] = buttons[i].asBool();
    }
  }
  catch (Json::Exception& e)
  {
    debug(WARNING, "GamePad::getFromString: %s\n", e.what());
    goto GET_FROM_STRING_ERROR;
  }

  game_pad->wakeAll();

  game_pad->unlock();
  return 0;

GET_FROM_STRING_ERROR:
  game_pad->unlock();
  return -1;
}

int GamePad::getMsg(char* msg, unsigned int max_length, unsigned int* length)
{
  debug(GAME_PAD, "getMsg\n");

  int ret;
  Json::Value root;
  if ((ret = getJson(root)) != 0)
  {
    return ret;
  }

  unsigned int l = root.toStyledString().length();
  if (l > max_length)
  {
    debug(WARNING, "GamePad::getMsg: To long %d > %d\n", l, max_length);
    return -1;
  }

  memcpy(msg, root.toStyledString().c_str(), l);
  // for (int i = 0; i < length; ++i)
  // {
  //   printf("%c", msg[i]);
  // }

  if (length != 0)
  {
    *length = l;
  }

  return 0;
}

int GamePad::getPrintableString(std::string& string)
{
  lock();
  std::string connected = connected_ == 1 ? "<connected>" : "<not connected>";
  std::string left      = "<" + std::to_string(left_.x_) + ", " + std::to_string(left_.y_) + ">";
  std::string right     = "<" + std::to_string(right_.x_) + ", " + std::to_string(right_.y_) + ">";
  std::string buttons   = "<";
  for (int i = 0; i < buttons_count_; ++i)
  {
    buttons += buttons_[i].load() ? "1" : "0";
    buttons += ", ";
  }
  buttons += std::to_string(lt_.load()) + ", " + std::to_string(rt_.load()) + ">";
  string = "controller " + connected + "\n" +
           "left " + left + "\n" +
           "right " + right + "\n" +
           "btn " + buttons;
  unlock();
  return 0;
}

int GamePad::getJson(Json::Value& root)
{
  lock();
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
    root[STRING_LT]    = lt_.load() ? 1 : 0;
    root[STRING_RT]    = rt_.load() ? 1 : 0;
    root[STRING_CON]   = connected_.load() ? 1 : 0;

    for (int i = 0; i < buttons_count_; ++i)
    {
      buttons[i] = buttons_[i].load()? 1 : 0;
    }
    root[STRING_BTN] = buttons;
  }
  catch (Json::Exception& e)
  {
    debug(WARNING, "GamePad::getjson: %s\n", e.what());
    goto GET_JSON_ERROR;
  }
  
  unlock();
  return 0;

GET_JSON_ERROR:
  unlock();
  return -1;
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

void GamePad::waitTillNewData(unsigned int timed)
{
  assert(cond_.heldByCurrentThread() == true);
  sleep(timed);
}
