#pragma once

#include <memory>
#include <shared_mutex>
#include <string>
#include <unordered_map>

class CommandExecutor;
class Logger;



class AsyncManager
{
public:
	static AsyncManager &getInstance();

	using Handle = void *;
	Handle connect(std::size_t blockSize);
	void receive(Handle handle, const std::string &buffer) const;
	void disconnect(Handle handle);

	// delete copy and move constructors and assign operators
	AsyncManager(AsyncManager const &) = delete;
	AsyncManager(AsyncManager &&) = delete;
	AsyncManager &operator=(AsyncManager const &) = delete;
	AsyncManager &operator=(AsyncManager &&) = delete;

private:
	AsyncManager();

	mutable std::shared_mutex _mutex;
	std::shared_ptr<Logger> _logger;
	std::unordered_map<Handle, std::unique_ptr<CommandExecutor>> _executors;
};
