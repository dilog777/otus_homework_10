#include "AsyncManager.h"



AsyncManager &AsyncManager::getInstance()
{
	static AsyncManager instance;
	return instance;
}



AsyncManager::Handle AsyncManager::connect([[maybe_unused]] std::size_t bulk)
{
	return nullptr;
}



void AsyncManager::receive([[maybe_unused]] Handle handle, [[maybe_unused]] const std::string &buffer)
{

}



void AsyncManager::disconnect([[maybe_unused]] Handle handle)
{

}
