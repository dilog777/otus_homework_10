#include "async.h"

#include "AsyncManager.h"



namespace async
{

handle_t connect(std::size_t bulk)
{
	return AsyncManager::getInstance().connect(bulk);
}



void receive(handle_t handle, const char *data, std::size_t size)
{
	AsyncManager::getInstance().receive(handle, std::string(data, size));
}



void disconnect(handle_t handle)
{
	AsyncManager::getInstance().disconnect(handle);
}

}
