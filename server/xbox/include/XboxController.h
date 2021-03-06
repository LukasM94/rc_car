#ifndef XBOX_CONTROLLER_H
#define XBOX_CONTROLLER_H

#include <stddef.h>
#include <linux/joystick.h>
#include <WorkingThread.h>

class XboxController : public WorkingThread
{
  public:
    static const char DEFAULT_PATH[];

    ~XboxController();

    static XboxController* instance(const char* path);
    static XboxController* instance();

    virtual void run();

    void print();
    inline static void print(XboxController* c)
    {
      c->print();
    }
    
    int readEvent(); 

  private:
    XboxController(XboxController& c);
    XboxController();
    XboxController(const char* path);

    static XboxController* instance_;

    inline bool isButton()
    {
      return event_.type == JS_EVENT_BUTTON;
    }
    inline bool isJoyStick()
    {
      return event_.type == JS_EVENT_AXIS;
    }
    inline bool isInit()
    {
      return event_.type == JS_EVENT_INIT;
    }

    int refreshButton();
    int refreshJoystick();

    const char* path_;

    int fd_;

    struct js_event event_;

    static const unsigned char LT_THRESHOLD = 64;
    static const unsigned char RT_THRESHOLD = 64;

    static const int AXIS_L_X = 0;
    static const int AXIS_L_Y = 1;
    static const int AXIS_R_X = 3;
    static const int AXIS_R_Y = 4;

    static const int BUTTON_LT = 2;
    static const int BUTTON_RT = 5;

    static const int BUTTON_A = 0;
    static const int BUTTON_B = 1;
    static const int BUTTON_X = 2;
    static const int BUTTON_Y = 3;

    static const int BUTTON_LB = 4;
    static const int BUTTON_RB = 5;

    static const int BUTTON_START  = 7;
    static const int BUTTON_BACK   = 6;
    static const int BUTTON_CIRCLE = 8;

    static const int BUTTON_COUNT = 9;
};

#endif