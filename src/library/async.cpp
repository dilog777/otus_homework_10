#include "async.h"

#include "AsyncManager.h"



namespace async
{

handle_t connect(std::size_t bulk)
{
	auto &manager = AsyncManager::getInstance();
	return manager.connect(bulk);
}



void receive(handle_t handle, const char *data, std::size_t size)
{
	auto &manager = AsyncManager::getInstance();
	manager.receive(handle, std::string(data, size));
}



void disconnect(handle_t handle)
{
	auto &manager = AsyncManager::getInstance();
	manager.disconnect(handle);
}

}
