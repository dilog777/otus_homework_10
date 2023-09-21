#include <iostream>

#include "AsyncManager.h"

const char *const USAGE_MESSAGE = "Usage: bulk_server <port> <bulk_size>";



int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cout << USAGE_MESSAGE << std::endl;
		return EXIT_FAILURE;
	}

	size_t port = static_cast<size_t>(atoi(argv[1]));
	size_t blockSize = static_cast<size_t>(atoll(argv[2]));

	std::cout << "port: " << port << " blockSize: " << blockSize << std::endl;

	AsyncManager asyncManager(blockSize);

	asyncManager.execute("client1", "cmd1");
	
	return EXIT_SUCCESS;
}
