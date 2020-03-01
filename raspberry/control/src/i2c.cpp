
#include <i2c.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <asm/ioctl.h>
#include <config.h>
#include <debug.h>

// I2C definitions

#define I2C_DEVICE "/dev/i2c-1"
#define I2C_SLAVE	0x0703
#define I2C_SMBUS	0x0720	/* SMBus-level access */

#define I2C_SMBUS_READ	1
#define I2C_SMBUS_WRITE	0

// SMBus transaction types

#define I2C_SMBUS_QUICK		          0
#define I2C_SMBUS_BYTE		          1
#define I2C_SMBUS_BYTE_DATA	        2 
#define I2C_SMBUS_WORD_DATA	        3
#define I2C_SMBUS_PROC_CALL	        4
#define I2C_SMBUS_BLOCK_DATA	      5
#define I2C_SMBUS_I2C_BLOCK_BROKEN  6
#define I2C_SMBUS_BLOCK_PROC_CALL   7		/* SMBus 2.0 */
#define I2C_SMBUS_I2C_BLOCK_DATA    8

// Data for SMBus Messages

#define I2C_SMBUS_BLOCK_MAX	32	/* As specified in SMBus standard */

union i2c_smbus_data 
{
	uint8_t  byte;
	uint16_t word;
	uint8_t  block[I2C_SMBUS_BLOCK_MAX + 2]; /* block[0] is used for length */
			       /* and one more for user-space compatibility */
};

// Structures used in the ioctl() calls

struct i2c_smbus_ioctl_data
{
  char    read_write;
  uint8_t command;
  int32_t size;

  union i2c_smbus_data* data;
};

static inline int i2c_smbus_access(int fd, char rw, uint8_t command, int size, union i2c_smbus_data* data)
{
  struct i2c_smbus_ioctl_data args;

  args.read_write = rw;
  args.command    = command;
  args.size       = size;
  args.data       = data;

  return ioctl(fd, I2C_SMBUS, &args);
}

I2c::I2c(const char* name, const int dev_address) : 
    Communication(name, Communication::TYPE_I2C)
{
  fd_ = wiringPiI2CSetupInterface(I2C_DEVICE, dev_address);
  debug(I2C, "I2c::I2c\n");
  if (fd_ <= 0)
  {
    debug(ERROR, "I2c::I2c: no device found\n");
    return;
  }
  if (gpioTestAndSet(RASPBERRY_I2C_SDA))
  {
    fd_ = -1;
    debug(ERROR, "I2c::I2c: sda already taken\n");
    return;
  }
  if (gpioTestAndSet(RASPBERRY_I2C_SCL))
  {
    fd_ = -1;
    gpioTestAndUnset(RASPBERRY_I2C_SDA);
    debug(ERROR, "I2c::I2c: scl already taken\n");
    return;
  }
  debug(I2C, "I2c::I2c: PIN %d is SDA\n", RASPBERRY_I2C_SDA);
  debug(I2C, "I2c::I2c: PIN %d is SCL\n", RASPBERRY_I2C_SCL);
}   

I2c::~I2c()
{

}

int I2c::writeByte(uint8_t reg, const uint8_t data)
{
  union i2c_smbus_data smbus_data;

  smbus_data.byte = data;
  debug(I2C, "I2c::writeByte reg <0x%x>, data <%d>\n", reg, smbus_data.byte);
  int ret = i2c_smbus_access(fd_, I2C_SMBUS_WRITE, reg, I2C_SMBUS_BYTE_DATA, &smbus_data);
  debug(I2C, "I2c::writeByte ret %d\n", ret);
  return ret;
}

int I2c::writeWord(uint8_t reg, const uint8_t* data)
{
  return writeBlock(reg, data, 2);
}

int I2c::writeBlock(uint8_t reg, const uint8_t* data, int length)
{
  union i2c_smbus_data smbus_data;

  if (length > I2C_SMBUS_BLOCK_MAX)
  {
    length = I2C_SMBUS_BLOCK_MAX;
  }
  
  smbus_data.block[0] = length;

  for (int i = 0; i < I2C_SMBUS_BLOCK_MAX; ++i)
  {
    smbus_data.block[1 + i] = data[i];
  }

  char string[6 * length];
  dataToHexArray(string, &smbus_data.block[1], length);

  debug(I2C, "I2c::writeBlock reg <0x%x>, length <%d>, data<%s>\n", reg, smbus_data.block[0], string);
  int ret = i2c_smbus_access(fd_, I2C_SMBUS_WRITE, reg, I2C_SMBUS_BLOCK_DATA, &smbus_data);
  debug(I2C, "I2c::writeBlock ret %d\n", ret);
  return ret;
}

void I2c::dataToHexArray(char* string, uint8_t* data, int length)
{
  static const char hex_chars[] = 
  {
    '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
  };
  char* c = string;
  int   i = 0;
  for (; i < length; ++i)
  {
    *c++ = '0';
    *c++ = 'x';
    *c++ = hex_chars[(data[i] & 0xf0) >> 4];
    *c++ = hex_chars[(data[i] & 0x0f)];
    *c++ = ',';
    *c++ = ' ';
  }
  --c;
  --c;
  *c = 0;
}

int I2c::write(uint8_t reg, const uint8_t* data, int length)
{
  if (length < 1)
  {
    return -1;
  }
  else if (length == 1)
  {
    return writeByte(reg, data[0]);
  }
  else if (length == 2)
  {
    return writeWord(reg, data);
  }
  else if (length < I2C_SMBUS_BLOCK_MAX)
  {
    return writeBlock(reg, data, length);
  }
  return -1;
}

int I2c::read(uint8_t reg, uint8_t* data, int lenght)
{
  return -1;
}