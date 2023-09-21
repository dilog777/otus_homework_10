#pragma once

#include <memory>
#include <string>
#include <unordered_map>

class CommandExecutor;
class ConsoleLogger;
class FileLogger;



class AsyncManager
{
public:
	AsyncManager(std::size_t blockSize);

	using ClientId = std::string;
	void execute(const ClientId &clientId, const std::string &commandStr);

private:
	std::size_t _blockSize;
	std::shared_ptr<ConsoleLogger> _consoleLogger;
	std::shared_ptr<FileLogger> _fileLogger;

	std::shared_ptr<CommandExecutor> _commonExecutor;
	std::unordered_map<ClientId, std::shared_ptr<CommandExecutor>> _clientExecutors;

	std::shared_ptr<CommandExecutor> makeExecutor() const;
};
