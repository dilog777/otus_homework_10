#pragma once

#include <list>
#include <memory>
#include <string>

#include "Command.h"

class BlockLogger;
class Command;
class CommandExecutor;



class CommandReader
{
public:
	CommandReader(const std::shared_ptr<CommandExecutor> &executor, const std::shared_ptr<BlockLogger> &logger, int blockSize);

	void run();

private:
	std::shared_ptr<CommandExecutor> _executor;
	std::shared_ptr<BlockLogger> _logger;
	int _blockSize { 0 };

	std::list<Command> _commands;
	int _deep { 0 };
};
