#pragma once

#include <string>



class ClientMessageHandler
{
public:
	using ClientId = std::string;

	virtual ~ClientMessageHandler() = default;

	virtual void ClientConnected(const ClientId &clientId) = 0;

	virtual void ClientMessage(const ClientId &clientId, const std::string &message) = 0;

	virtual void ClientDisconnected(const ClientId &clientId) = 0;
};
