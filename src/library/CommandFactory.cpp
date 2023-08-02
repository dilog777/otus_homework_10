#include "CommandFactory.h"

#include "CommandBeginBlock.h"
#include "CommandEndBlock.h"
#include "CommandText.h"



const char *const BEGIN_BLOCK_COMMAND = "{";
const char *const END_BLOCK_COMMAND = "}";



std::shared_ptr<Command> CommandFactory::makeCommand(const std::string &str)
{
	if (str == BEGIN_BLOCK_COMMAND)
	{
		return std::make_shared<CommandBeginBlock>();
	}
	else if (str == END_BLOCK_COMMAND)
	{
		return std::make_shared<CommandEndBlock>();
	}

	return std::make_shared<CommandText>(str);
}
