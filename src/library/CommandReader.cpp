#include "CommandReader.h"

#include <iostream>

#include "CommandExecutor.h"
#include "BlockLogger.h"


const int DEFAULT_BLOCK_SIZE = 3;



CommandReader::CommandReader(const std::shared_ptr<CommandExecutor> &executor, const std::shared_ptr<BlockLogger> &logger, size_t blockSize)
	: _executor { executor }
	, _logger { logger }
	, _blockSize { blockSize }
{
	if (_blockSize == 0)
		_blockSize = DEFAULT_BLOCK_SIZE;
}



void CommandReader::run()
{
	std::string line;
	while (std::getline(std::cin, line))
	{
		if (line == "{")
		{
			++_deep;
		}
		else if (line == "}")
		{
			if (_deep == 0)
				continue;

			--_deep;

			if (_deep == 0)
			{
				_executor->execute(_commands);
				_commands.clear();
			}
		}
		else
		{
			if (_commands.empty())
				_logger->startBlock();
			
			_commands.emplace_back(line);

			if (_deep == 0 && _commands.size() >= _blockSize)
			{
				_executor->execute(_commands);
				_commands.clear();
			}
		}
	}
}
