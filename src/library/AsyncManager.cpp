#include "AsyncManager.h"



AsyncManager &AsyncManager::getInstance()
{
	static AsyncManager instance;
	return instance;
}



AsyncManager::Handle AsyncManager::connect(std::size_t bulk)
{
	return nullptr;
}



void AsyncManager::receive(Handle handle, const std::string &buffer)
{

}



void AsyncManager::disconnect(Handle handle)
{

}
