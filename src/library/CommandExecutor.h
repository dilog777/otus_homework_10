#pragma once

#include <memory>

#include "GlobalMacroses.h"

class Command;
class Logger;



class CommandExecutor
{
	DISABLE_COPY(CommandExecutor)

public:
	CommandExecutor(size_t blockSize);
	~CommandExecutor();

	void addLogger(const std::shared_ptr<Logger> &logger);

	void execute(const std::shared_ptr<Command> &command);

	bool dynamicMode() const;

private:
	class Impl;
	Impl *_impl { nullptr };
};
