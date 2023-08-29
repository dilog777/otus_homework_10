#pragma once

#include <memory>
#include <string>

class Logger;



class CommandExecutor
{
public:
	CommandExecutor(size_t blockSize);
	~CommandExecutor();

	void addLogger(const std::shared_ptr<Logger> &logger);

	void execute(const std::string &buffer);

private:
	class Impl;
	Impl *_impl { nullptr };
};
