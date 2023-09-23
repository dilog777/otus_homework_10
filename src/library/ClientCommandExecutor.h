#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "ClientMessageHandler.h"

class CommandExecutor;
class ConsoleLogger;
class FileLogger;



class ClientCommandExecutor : public ClientMessageHandler
{
public:
	ClientCommandExecutor(std::size_t blockSize);

	void ClientConnected(const ClientId &clientId) override;

	void ClientMessage(const ClientId &clientId, const std::string &message) override;

	void ClientDisconnected(const ClientId &clientId) override;

private:
	std::size_t _blockSize;
	std::shared_ptr<ConsoleLogger> _consoleLogger;
	std::shared_ptr<FileLogger> _fileLogger;

	std::shared_ptr<CommandExecutor> _commonExecutor;
	std::unordered_map<ClientId, std::shared_ptr<CommandExecutor>> _clientExecutors;

	std::shared_ptr<CommandExecutor> makeExecutor() const;
};
