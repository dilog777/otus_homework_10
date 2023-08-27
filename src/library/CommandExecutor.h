#pragma once

#include <memory>
#include <string>

class Command;
class Logger;



class CommandExecutor
{
public:
	CommandExecutor(const std::shared_ptr<Logger> &logger, size_t blockSize);
	~CommandExecutor();

	void execute(const std::string &buffer);

private:
	class Impl;
	Impl *_impl { nullptr };
};
