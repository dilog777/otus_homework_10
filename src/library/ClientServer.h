#pragma once

#include <memory>

class ClientMessageHandler;



class ClientServer
{
public:
	ClientServer(const std::shared_ptr<ClientMessageHandler> &messageHandler);
	~ClientServer();

	ClientServer(ClientServer const &) = delete;
	ClientServer &operator=(ClientServer const &) = delete;

	using Port = unsigned short;
	void run(Port port);

private:
	class Impl;
	Impl *_impl { nullptr };
};
