#include <Atmega.h>
#include <string.h>
#include <Gpio.h>
#include <i2c_protocol.h>
#include <debug.h>
#include <ControlHandler.h>
#include <GamePad.h>
#include <unistd.h>

//--------------------------------------------------------------------
ControlHandler::ControlHandler(GamePad* game_pad) : 
  atmega_(0),
  game_pad_(game_pad)
{
  debug(CTL_HANLER, "ctor: game_pad <%p>\n", game_pad_);
}

//--------------------------------------------------------------------
ControlHandler::~ControlHandler()
{
  debug(CTL_HANLER, "dtor\n");
}

//--------------------------------------------------------------------
void ControlHandler::gpioInit()
{
  debug(CTL_HANLER, "gpioInit\n");
  Gpio::instance()->initLed();
  Gpio::instance()->initButton(&buttonCallback);
}

//--------------------------------------------------------------------
void ControlHandler::i2cInit()
{
  debug(CTL_HANLER, "i2cInit\n");
  atmega_ = new Atmega();
}

//--------------------------------------------------------------------
void ControlHandler::buttonCallback()
{
  debug(CTL_HANLER, "buttonCallback: Button pressed\n");
}

//--------------------------------------------------------------------
void* ControlHandler::gpioFunction(void* arg)
{
  ControlHandler* ch = (ControlHandler*)arg;

  debug(CTL_HANLER, "gpioFunction: Start\n");
  while (running)
  {
    Gpio::instance()->heartBeat();
  }
  debug(CTL_HANLER, "gpioFunction: Exit\n");
  return 0;
}

//--------------------------------------------------------------------
void* ControlHandler::i2cFunction(void* arg)
{
  ControlHandler* ch = (ControlHandler*)arg;

  debug(CTL_HANLER, "i2cFunction: Start\n");
  while (running)
  {
    int      reg   = I2C_MOTOR;
    uint16_t speed = 0x1234;
    ch->atmega_->writeI2c(reg, (const uint8_t*)&speed, 2); 
    usleep(500000); 
  }
  debug(CTL_HANLER, "i2cFunction: Exit\n");
  return 0;
}













//--------------------------------------------------------------------
pthread_t    tid_i2c;
volatile int running = 1;
Atmega*      atmega;

//--------------------------------------------------------------------
void  gpioInit();
void  i2cInit();
void  buttonCallback();
void* i2cFunction(void* arg);

//--------------------------------------------------------------------
int control(int argc, char* argv[])
{
  gpioInit();
  i2cInit();

  debug(CONTROL, "control: Finish with initialization\n");

  pthread_create(&tid_i2c, 0, i2cFunction, 0);

  debug(CONTROL, "control: Start hear beat\n");

  while (running)
  {
    Gpio::instance()->heartBeat();
  }
  debug(CONTROL, "control: End hear beat\n");
  return 0;
}

//--------------------------------------------------------------------
void gpioInit()
{
  Gpio::instance()->initLed();
  Gpio::instance()->initButton(&buttonCallback);
}

//--------------------------------------------------------------------
void i2cInit()
{
  atmega = new Atmega();
}

//--------------------------------------------------------------------
void buttonCallback()
{
  debug(CONTROL, "buttonCallback: Button pressed\n");
}

//--------------------------------------------------------------------
void* i2cFunction(void* arg)
{
  debug(CONTROL, "i2cFunction: Start\n");
  while (running)
  {
    int      reg   = I2C_MOTOR;
    uint16_t speed = 0x1234;
    atmega->writeI2c(reg, (const uint8_t*)&speed, 2); 
    usleep(500000); 
  }
  debug(CONTROL, "i2cFunction: End\n");
  return 0;
}
