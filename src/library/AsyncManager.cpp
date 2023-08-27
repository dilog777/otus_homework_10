#include "AsyncManager.h"

#include "CommandExecutor.h"
#include "Logger.h"



AsyncManager &AsyncManager::getInstance()
{
	static AsyncManager instance;
	return instance;
}



AsyncManager::Handle AsyncManager::connect(std::size_t blockSize)
{
	auto logger = std::make_shared<Logger>();
	auto executor = std::make_unique<CommandExecutor>(logger, blockSize);
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
