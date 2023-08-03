#pragma once

#include <memory>

class Command;
class Logger;



class CommandExecutor
{
public:
	CommandExecutor(const std::shared_ptr<Logger> &logger, size_t blockSize);
	~CommandExecutor();

	void execute(const std::shared_ptr<Command> &command);
	void finish();

private:
	class Impl;
	Impl *_impl { nullptr };
};
