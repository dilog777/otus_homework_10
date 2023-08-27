#pragma once

#include <memory>
#include <shared_mutex>
#include <string>

#include <unordered_map>

class CommandExecutor;



class AsyncManager
{
public:
	static AsyncManager &getInstance();

	using Handle = void *;

	Handle connect(std::size_t blockSize);
	void receive(Handle handle, const std::string &buffer) const;
	void disconnect(Handle handle);

	// delete copy and move constructors and assign operators
	AsyncManager(AsyncManager const &) = delete;            // Copy construct
	AsyncManager(AsyncManager &&) = delete;                 // Move construct
	AsyncManager &operator=(AsyncManager const &) = delete; // Copy assign
	AsyncManager &operator=(AsyncManager &&) = delete;      // Move assign

private:
	AsyncManager() = default;

	mutable std::shared_mutex _mutex;
	std::unordered_map<Handle, std::unique_ptr<CommandExecutor>> _executors;
};
