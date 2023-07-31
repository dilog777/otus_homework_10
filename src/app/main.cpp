#include <iostream>

#include "BlockLogger.h"
#include "CommandExecutor.h"
#include "CommandReader.h"

const char *const USAGE_MESSAGE = "Usage: bulk %d";



int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << USAGE_MESSAGE << std::endl;
		return 1;
	}
	
	size_t blockSize = static_cast<size_t>(atoi(argv[1]));

	auto logger = std::make_shared<BlockLogger>();
	auto executor = std::make_shared<CommandExecutor>(logger);
	auto reader = std::make_shared<CommandReader>(executor, logger, blockSize);
	
	reader->run();

	return 0;
}
