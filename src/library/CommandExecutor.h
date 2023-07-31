#pragma once

#include <list>
#include <memory>
#include <string>

class Command;
class Logger;



class CommandExecutor
{
public:
	CommandExecutor(const std::shared_ptr<Logger> &logger);

	void execute(const std::list<Command> &commands);

private:
	std::shared_ptr<Logger> _logger;

	std::string names(const std::list<Command> &commands) const;
};
