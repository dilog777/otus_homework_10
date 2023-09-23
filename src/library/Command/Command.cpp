#include "Command.h"



Command::Command(Type type)
	: _type { type }
{
}



Command::Type Command::type() const
{
	return _type;
};
