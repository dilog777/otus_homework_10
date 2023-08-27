#include "CommandExecutor.h"

#include <cassert>
#include <chrono>
#include <list>
#include <numeric>
#include <sstream>

#include "Command/Command.h"
#include "CommandFactory.h"
#include "CommandMachine.h"
#include "Logger.h"

using system_clock = std::chrono::system_clock;



const char *const COMMAND_DELIMITER = ", ";
const char *const COMMAND_OUT_PREFIX = "bulk: ";



class CommandExecutor::Impl : public CommandMachine
{
public:
	Impl(const std::shared_ptr<Logger> &logger, size_t blockSize);
	~Impl();

	// CommandMachine interface
	void beginBlock() override;
	void endBlock() override;
	void textCommand(const std::string &text) override;

private:
	std::shared_ptr<Logger> _logger;
	size_t _blockSize { 0 };

	time_t _beginBlockTime { 0 };

	int _deep { 0 };
	std::list<std::string> _textBuffer;

	std::string join(std::list<std::string> const &strings, std::string delim) const;

	void outTextBuffer();
	time_t currentTime() const;
};



CommandExecutor::Impl::Impl(const std::shared_ptr<Logger> &logger, size_t blockSize)
	: _logger { logger }
	, _blockSize { blockSize }
{
	assert(_blockSize > 0);
}



CommandExecutor::Impl::~Impl()
{
	if (_deep == 0)
		outTextBuffer();
}



void CommandExecutor::Impl::beginBlock()
{
	if (_deep == 0)
		outTextBuffer();

	++_deep;
}



void CommandExecutor::Impl::endBlock()
{
	if (_deep == 0)
		return;

	--_deep;

	if (_deep == 0)
		outTextBuffer();
}



void CommandExecutor::Impl::textCommand(const std::string &text)
{
	if (_textBuffer.empty())
		_beginBlockTime = currentTime();

	_textBuffer.push_back(text);

	if (_deep == 0 && _textBuffer.size() >= _blockSize)
		outTextBuffer();
}



void CommandExecutor::Impl::outTextBuffer()
{
	if (_textBuffer.empty())
		return;

	std::string result = COMMAND_OUT_PREFIX + join(_textBuffer, COMMAND_DELIMITER);
	_logger->log(_beginBlockTime, result);
	_textBuffer.clear();
}



time_t CommandExecutor::Impl::currentTime() const
{
	auto now = system_clock::now();
	return system_clock::to_time_t(now);
}



std::string CommandExecutor::Impl::join(std::list<std::string> const &strings, std::string delim) const
{
	auto joinFunc = [&delim](const std::string &str1, const std::string &str2)
	{
		return (str1.empty() ? str2 : str1 + delim + str2);
	};

	return std::accumulate(strings.begin(), strings.end(), std::string(), joinFunc);
}



CommandExecutor::CommandExecutor(const std::shared_ptr<Logger> &logger, size_t blockSize)
	: _impl { new Impl(logger, blockSize) }
{
}



CommandExecutor::~CommandExecutor()
{
	delete _impl;
}



void CommandExecutor::execute(const std::string &buffer)
{
	std::stringstream ss(buffer);
	std::string str;
	while (std::getline(ss, str))
	{
		auto command = CommandFactory::makeCommand(str);
		command->execute(_impl);
	}
}
