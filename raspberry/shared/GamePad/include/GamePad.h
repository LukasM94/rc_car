#ifndef GAME_PAD_H
#define GAME_PAD_H

#include <stdint.h>
#include <string>
#include <Lock.h>
#include <atomic>
#include <debug.h>

struct axis_state 
{
  std::atomic_int8_t x_;
  std::atomic_int8_t y_;
};

namespace Json
{
  class Value;
}

class GamePad
{
  public:
    GamePad();
    GamePad(uint8_t button_count);
    ~GamePad();

    static int getFromString(GamePad* game_pad, const char* str);

    int getMsg(char* msg, unsigned int max_length);

    int getPrintableString(std::string& string);

    int setButton(uint8_t button_no, bool state)
    {
      if (button_no < buttons_count_)
      {
        buttons_[button_no] = state;
        return 0;
      }
      return 1;
    }
    inline void setLTButton(bool state)
    {
      lt_ = state;
    }
    inline void setRTButton(bool state)
    {
      rt_ = state;
    }
    inline void setLeftAxisX(int8_t x)
    { 
      left_.x_ = x;
    }
    inline void setLeftAxisY(int8_t y)
    {
      left_.y_ = y;
    }
    inline void setRightAxisX(int8_t x)
    {
      right_.x_ = x;
    }
    inline void setRightAxisY(int8_t y)
    {
      right_.y_ = y;
    }

    inline bool getButton(uint8_t button_no)
    {
      return (buttons_count_ > button_no) && buttons_[button_no];
    }
    inline bool getLTButton()
    {
      return lt_;
    }
    inline bool getRTButton()
    {
      return rt_;
    }
    inline int8_t getLeftAxisX()
    {
      return left_.x_;
    }
    inline int8_t getLeftAxisY()
    {
      return left_.y_;
    }
    inline int8_t getRightAxisX()
    {
      return right_.x_;
    }
    inline int8_t getRightAxisY()
    {
      return right_.y_;
    }
    inline uint8_t getButtonCnt()
    {
      return buttons_count_;
    }

    inline void lock()
    {
      lock_.lock();
    }
    inline void unlock()
    {
      lock_.unlock();
    }
    void reset();

    inline bool isNew()
    {
      return refreshed_.exchange(false);
    }

    inline void setConnected()
    {
      connected_ = 1;
    }
    inline void setUnconnected()
    {
      connected_ = 0;
    }

    static const unsigned int BUTTON_A      = 0;
    static const unsigned int BUTTON_B      = 1;
    static const unsigned int BUTTON_X      = 2;
    static const unsigned int BUTTON_Y      = 3;
    static const unsigned int BUTTON_LB     = 4;
    static const unsigned int BUTTON_RB     = 5;
    static const unsigned int BUTTON_SELECT = 6;
    static const unsigned int BUTTON_START  = 7;
    static const unsigned int BUTTON_CIRCLE = 8;

  private:
    int  getJson(Json::Value& root);
    void fromPackage(const char* package);
    void allocateButtons(unsigned int button_ctn);

    struct axis_state left_;
    struct axis_state right_;

    std::atomic_bool    lt_;
    std::atomic_bool    rt_;
    std::atomic_uint8_t buttons_count_;
    std::atomic_bool*   buttons_;
    std::atomic_bool    connected_;

    std::atomic_bool refreshed_;

    Lock lock_;

    static const char STRING_LEFT[];
    static const char STRING_RIGHT[];
    static const char STRING_LT[];
    static const char STRING_RT[];
    static const char STRING_BCNT[];
    static const char STRING_BTN[];
};

#endif