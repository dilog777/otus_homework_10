#pragma once

#include <memory>

class ClientMessageHandler;



class ClientServer
{
public:
	using Port = unsigned short;

	ClientServer(const std::shared_ptr<ClientMessageHandler> &messageHandler);
	~ClientServer();

	void run(Port port);

private:
	class Impl;
	Impl *_impl { nullptr };
};
