#pragma once

#include <list>
#include <memory>
#include <string>

#include "CommandMachine.h"

class Command;
class Logger;



class CommandExecutor : public CommandMachine
{
public:
	CommandExecutor(const std::shared_ptr<Logger> &logger, size_t blockSize);

	void execute(const std::shared_ptr<Command> &command);
	void finish();

	void beginBlock() override;
	void endBlock() override;
	void textCommand(const std::string &text) override;

private:
	std::shared_ptr<Logger> _logger;
	size_t _blockSize { 0 };

	int _deep { 0 };
	std::list<std::string> _textBuffer;

	void outTextBuffer();

	std::string join(std::list<std::string> const &strings, std::string delim) const;
};
