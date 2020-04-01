
#include <Communication.h>
#include <debug.h>

Communication::~Communication()
{
  debug(COM, "Communication::~Communication()\n");
}

Communication::Communication(std::string name, enum Type type) : 
    name_(name), 
    type_(type)
{
  debug(COM, "ctor: name <%s>\n", name_.c_str());
}

std::string& Communication::getName()
{
  return name_;
}

enum Communication::Type Communication::getType()
{
  return type_;
}
