#include "CommandExecutor.h"

#include "Command.h"
#include "Logger.h"

const char *const COMMAND_NAMES_DELIMITER = ", ";
const char *const COMMAND_OUT_PREFIX = "bulk: ";



CommandExecutor::CommandExecutor(const std::shared_ptr<Logger> &logger)
	: _logger { logger }
{
}



void CommandExecutor::execute(const std::list<Command> &commands)
{
	std::string result = COMMAND_OUT_PREFIX + names(commands);
	_logger->log(result);
}



std::string CommandExecutor::names(const std::list<Command> &commands) const
{
	std::string result;
	for (const auto &command : commands)
	{
		if (!result.empty())
			result += COMMAND_NAMES_DELIMITER;

		result += command.name();
	}
	return result;
}