#include "AsyncManager.h"

#include <mutex>

#include "CommandExecutor.h"
#include "ConsoleLogger.h"
#include "FileLogger.h"



AsyncManager &AsyncManager::getInstance()
{
	static AsyncManager instance;
	return instance;
}



AsyncManager::Handle AsyncManager::connect(std::size_t blockSize)
{
	auto executor = std::make_unique<CommandExecutor>(blockSize);
	executor->addLogger(_consoleLogger);
	executor->addLogger(_fileLogger);

	Handle handle = executor.get();

	std::unique_lock lock { _mutex };
	_executors[handle] = std::move(executor);

	return handle;
}



void AsyncManager::receive(Handle handle, const std::string &buffer) const
{
	std::shared_lock lock { _mutex };

	if (_executors.count(handle) == 0)
		return;

	_executors.at(handle)->execute(buffer);
}



void AsyncManager::disconnect(Handle handle)
{
	std::unique_lock lock { _mutex };

	if (_executors.count(handle) == 0)
		return;

	_executors.erase(handle);
}



AsyncManager::AsyncManager()
	: _consoleLogger { new ConsoleLogger }
	, _fileLogger { new FileLogger }
{
}
