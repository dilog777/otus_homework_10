#include "ClientCommandExecutor.h"

#include "Command/Command.h"
#include "CommandExecutor.h"
#include "CommandFactory.h"
#include "ConsoleLogger.h"
#include "FileLogger.h"



ClientCommandExecutor::ClientCommandExecutor(std::size_t blockSize)
	: _blockSize { blockSize }
	, _consoleLogger { new ConsoleLogger }
	, _fileLogger { new FileLogger }
{
	_commonExecutor = makeExecutor();
}



void ClientCommandExecutor::ClientConnected([[maybe_unused]] const ClientId &clientId)
{
}



void ClientCommandExecutor::ClientMessage(const ClientId &clientId, const std::string &message)
{
	auto command = CommandFactory::makeCommand(message);

	if (_clientExecutors.count(clientId) != 0)
	{
		auto &executor = _clientExecutors.at(clientId);
		executor->execute(command);

		if (!executor->dynamicMode())
			_clientExecutors.erase(clientId);
	}
	else if (command->type() == Command::Type::BeginBlock)
	{
		_clientExecutors[clientId] = makeExecutor();
		_clientExecutors.at(clientId)->execute(command);
	}
	else
	{
		_commonExecutor->execute(command);
	}
}



void ClientCommandExecutor::ClientDisconnected(const ClientId &clientId)
{
	_clientExecutors.erase(clientId);
}



std::shared_ptr<CommandExecutor> ClientCommandExecutor::makeExecutor() const
{
	auto executor = std::make_shared<CommandExecutor>(_blockSize);
	executor->addLogger(_consoleLogger);
	executor->addLogger(_fileLogger);
	return executor;
}
