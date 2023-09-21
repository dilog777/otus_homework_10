#include "AsyncManager.h"

#include "Command/Command.h"
#include "CommandExecutor.h"
#include "CommandFactory.h"
#include "ConsoleLogger.h"
#include "FileLogger.h"



AsyncManager::AsyncManager(std::size_t blockSize)
	: _blockSize { blockSize }
	, _consoleLogger { new ConsoleLogger }
	, _fileLogger { new FileLogger }
{
	_commonExecutor = makeExecutor();
}



void AsyncManager::execute(const ClientId &clientId, const std::string &commandStr)
{
	auto command = CommandFactory::makeCommand(commandStr);

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



std::shared_ptr<CommandExecutor> AsyncManager::makeExecutor() const
{
	auto executor = std::make_shared<CommandExecutor>(_blockSize);
	executor->addLogger(_consoleLogger);
	executor->addLogger(_fileLogger);
	return executor;
}
