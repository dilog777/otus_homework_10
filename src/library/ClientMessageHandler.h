#pragma once

#include <string>



class ClientMessageHandler
{
public:
	using ClientId = void *;

	virtual ~ClientMessageHandler() = default;

	virtual void ClientConnected(const ClientId &clientId) = 0;

	virtual void ClientSendMessage(const ClientId &clientId, const std::string &message) = 0;

	virtual void ClientDisconnected(const ClientId &clientId) = 0;
};
