
#include <communication.h>
#include <debug.h>

Communication::Communication()
{

}

Communication::~Communication()
{
  debug(COM, "Communication::~Communication()\n");
}

Communication::Communication(const char* name, enum Type type) : 
    name_(name), 
    type_(type)
{
  debug(COM, "Communication::Communication(const char* %s)\n", name_);
}

const char* Communication::getName()
{
  return name_;
}

enum Communication::Type Communication::getType()
{
  return type_;
}
