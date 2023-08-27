#pragma once

#include <cstddef>
#include <string>



class AsyncManager
{
public:
	static AsyncManager &getInstance();

	// delete copy and move constructors and assign operators
	AsyncManager(AsyncManager const &) = delete;            // Copy construct
	AsyncManager(AsyncManager &&) = delete;                 // Move construct
	AsyncManager &operator=(AsyncManager const &) = delete; // Copy assign
	AsyncManager &operator=(AsyncManager &&) = delete;      // Move assign




	using Handle = void *;

	Handle connect(std::size_t bulk);
	void receive(Handle handle, const std::string &buffer);
	void disconnect(Handle handle);

private:
	AsyncManager() = default;

};
