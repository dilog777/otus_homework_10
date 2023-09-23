#include "ClientServer.h"

#include <iostream>

#include <boost/algorithm/string/trim_all.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/streambuf.hpp>

#include "ClientMessageHandler.h"

namespace asio = boost::asio;
using tcp = asio::ip::tcp;



class ClientServer::Impl
{
public:
	Impl(const std::shared_ptr<ClientMessageHandler> &messageHandler);

	asio::awaitable<void> listenPort(Port port);
	asio::awaitable<void> listenClient(tcp::socket socket);

private:
	std::shared_ptr<ClientMessageHandler> _messageHandler;
};



ClientServer::Impl::Impl(const std::shared_ptr<ClientMessageHandler> &messageHandler)
	: _messageHandler { messageHandler }
{
}



asio::awaitable<void> ClientServer::Impl::listenPort(Port port)
{
	const auto executor = co_await asio::this_coro::executor;

	tcp::acceptor acceptor { executor, { tcp::v4(), port } };

	for (;;)
	{
		auto socket = co_await acceptor.async_accept(asio::use_awaitable);

		asio::co_spawn(executor, listenClient(std::move(socket)), asio::detached);
	}
}



asio::awaitable<void> ClientServer::Impl::listenClient(tcp::socket socket)
{
	std::string clientName;
	asio::streambuf buffer;

	for (;;)
	{
		try
		{
			co_await asio::async_read_until(socket, buffer, "\n", asio::use_awaitable);
		}
		catch (const boost::system::system_error &)
		{
			break;
		}

		std::string message(asio::buffer_cast<const char *>(buffer.data()), buffer.size());
		boost::trim(message);

		buffer.consume(buffer.size());

		if (clientName.empty())
		{
			clientName = message;

			//std::cout << "Client \"" << clientName << "\": Connected." << std::endl;

			_messageHandler->ClientConnected(clientName);

			continue;
		}
		else
		{
			//std::cout << " Client \"" << clientName << "\": Sending: " << message << std::endl;

			_messageHandler->ClientMessage(clientName, message);
		}
	}

	//std::cout << " Client \"" << clientName << "\": Disconnected." << std::endl;

	_messageHandler->ClientDisconnected(clientName);
}



ClientServer::ClientServer(const std::shared_ptr<ClientMessageHandler> &messageHandler)
	: _impl { new Impl(messageHandler) }
{
}



ClientServer::~ClientServer()
{
	delete _impl;
}



void ClientServer::run(Port port)
{
	asio::io_context ioContext;

	asio::signal_set signals { ioContext, SIGINT, SIGTERM };
	signals.async_wait([&](auto, auto){ ioContext.stop(); });

	asio::co_spawn(ioContext, _impl->listenPort(port), asio::detached);

	ioContext.run();
}
