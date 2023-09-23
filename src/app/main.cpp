#include <iostream>

#include <boost/lexical_cast.hpp>

#include "ClientCommandExecutor.h"
#include "ClientServer.h"

const char *const USAGE_MESSAGE = "Usage: bulk_server <port> <bulk_size>";



template<class T>
T stringToType(const std::string &string)
{
	try
	{
		return boost::lexical_cast<T>(string);
	}
	catch (boost::bad_lexical_cast &)
	{
		return {};
	}
}



int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cout << USAGE_MESSAGE << std::endl;
		return EXIT_FAILURE;
	}

	auto port = stringToType<ClientServer::Port>(argv[1]);
	auto blockSize = stringToType<size_t>(argv[2]);

	auto commandExecutor = std::make_shared<ClientCommandExecutor>(blockSize);
	ClientServer server(commandExecutor);

	server.run(port);
	
	return EXIT_SUCCESS;
}
