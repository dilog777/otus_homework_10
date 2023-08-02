#include "CommandExecutor.h"

#include <cassert>
#include <numeric>

#include "Command.h"
#include "Logger.h"


const char *const COMMAND_DELIMITER = ", ";
const char *const COMMAND_OUT_PREFIX = "bulk: ";



CommandExecutor::CommandExecutor(const std::shared_ptr<Logger> &logger, size_t blockSize)
	: _logger { logger }
	, _blockSize { blockSize }
{
	assert(_blockSize > 0);
}



void CommandExecutor::execute(const std::shared_ptr<Command> &command)
{
	command->execute(this);
}



void CommandExecutor::finish()
{
	outTextBuffer();
}



void CommandExecutor::beginBlock()
{
	++_deep;
}



void CommandExecutor::endBlock()
{
	if (_deep == 0)
		return;

	--_deep;

	if (_deep == 0)
		outTextBuffer();
}



void CommandExecutor::textCommand(const std::string &text)
{
	if (_textBuffer.empty())
		_logger->beginBlock();
	
	_textBuffer.push_back(text);

	if (_deep == 0 && _textBuffer.size() >= _blockSize)
		outTextBuffer();
}



void CommandExecutor::outTextBuffer()
{
	if (_textBuffer.empty())
		return;

	std::string result = COMMAND_OUT_PREFIX + join(_textBuffer, COMMAND_DELIMITER);
	_logger->log(result);
	_textBuffer.clear();
}



std::string CommandExecutor::join(std::list<std::string> const &strings, std::string delim) const
{
	auto joinFunc = [&delim](const std::string &str1, const std::string &str2)
	{
		return (str1.empty() ? str2 : str1 + delim + str2);
	};

	return std::accumulate(strings.begin(), strings.end(), std::string(), joinFunc);
}
