#include "Command.h"



Command::Command(const std::string &name)
	: _name { name }
{
}



const std::string &Command::name() const
{
	return _name;
}
