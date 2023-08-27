#include "CommandReader.h"

#include <iostream>

#include "CommandFactory.h"
#include "CommandExecutor.h"



CommandReader::CommandReader(const std::shared_ptr<CommandExecutor> &executor)
	: _executor { executor }
{
}



void CommandReader::run()
{
	std::string str;
	while (std::getline(std::cin, str))
	{
		auto command = CommandFactory::makeCommand(str);
		_executor->execute(command);
	}
	_executor->finish();
}
