#pragma once

#include <memory>

class CommandExecutor;



class CommandReader
{
public:
	CommandReader(const std::shared_ptr<CommandExecutor> &executor);

	void run();

private:
	std::shared_ptr<CommandExecutor> _executor;
};
