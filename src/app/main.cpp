#include <iostream>

#include "CommandExecutor.h"
#include "CommandReader.h"
#include "Logger.h"

const char *const USAGE_MESSAGE = "Usage: bulk %d";



int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << USAGE_MESSAGE << std::endl;
		return 1;
	}
	
	size_t blockSize = static_cast<size_t>(atoi(argv[1]));

	auto logger = std::make_shared<Logger>();
	auto executor = std::make_shared<CommandExecutor>(logger, blockSize);
	auto reader = std::make_shared<CommandReader>(executor);
	
	reader->run();

	return 0;
}
