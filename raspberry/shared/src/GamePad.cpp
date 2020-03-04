
#include <GamePad.h>
#include <string>
#include <algorithm>
#include <string>
#include <string.h>
#include <debug.h>
#if defined(__i386__)
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

GamePad::GamePad(uint8_t button_count) :
  lt_(0),
  rt_(0),
  buttons_count_(button_count),
  buttons_(new std::atomic_bool[buttons_count_])
{
  debug(GAME_PAD, "ctor\n");
  pthread_mutex_init(&lock_, 0);
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

GamePad* GamePad::getFromString(GamePad* game_pad, const char* str)
{
  debug(GAME_PAD, "getFromString\n");

  Json::Value  root;
  Json::Reader reader;
  Json::Value  left;
  Json::Value  right;
  Json::Value  buttons;

  int ret = reader.parse(str, root);
  if (ret == 0)
  {
    debug(ERROR, "GamePad::getMsg: parsing not successful\n");
    return 0;
  }

  buttons = root[STRING_BTN];
  left    = root[STRING_LEFT];
  right   = root[STRING_RIGHT];

  unsigned int button_cnt = buttons.size();

  if (game_pad == 0)
  {
    game_pad = new GamePad(button_cnt);
  }
  if (game_pad->getButtonCnt() != button_cnt)
  {
    delete game_pad;
    game_pad = new GamePad(button_cnt);
  }

  game_pad->left_.x_  = left[0].asBool();  
  game_pad->left_.y_  = left[1].asBool();  
  game_pad->right_.x_ = right[0].asBool();  
  game_pad->right_.y_ = right[1].asBool();  

  game_pad->rt_ = root[STRING_RT].asBool();
  game_pad->lt_ = root[STRING_LT].asBool();

  for (int i = 0; i < button_cnt; ++i)
  {
    game_pad->buttons_[i] = buttons[i].asBool();
  }

  return game_pad;
}

int GamePad::getMsg(char* msg, unsigned int max_length)
{
  debug(GAME_PAD, "getMsg\n");

  Json::Value root;
  getJson(root);

  unsigned int length = root.toStyledString().length();
  if (length > max_length)
  {
    return -1;
  }

  memcpy(msg, root.toStyledString().c_str(), length);
  return 0;
}

void GamePad::getJson(Json::Value& root)
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
  // root[STRING_BCNT]       = buttons_count_.load();

  for (int i = 0; i < buttons_count_; ++i)
  {
    buttons[i] = buttons_[i].load()? 1 : 0;
  }
  root[STRING_BTN] = buttons;
}

void GamePad::getMsg(char** msg, unsigned int* length)
{
  debug(GAME_PAD, "getMsg: Start\n");

  Json::Value root;
  getJson(root);

  *length = root.toStyledString().length();
  *msg    = new char[*length];
  memcpy(*msg, root.toStyledString().c_str(), *length);

  if (OUTPUT_ENABLED & OUTPUT_ENABLED)
  {
    std::string temp = root.toStyledString();
    temp.erase(std::remove(temp.begin(), temp.end(), '\n'), temp.end());
    temp.erase(std::remove(temp.begin(), temp.end(), '\t'), temp.end());
    debug(GAME_PAD, "%s\n", temp.c_str());
  }
}
