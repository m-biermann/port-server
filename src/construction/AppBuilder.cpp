//
// Created by max on 8/18/20.
//

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include "AppBuilder.h"
#include "../TcpAcceptor.h"

namespace mabiphmo::portServer::construction {
	iocServer::construction::IAppBuilder &AppBuilder::BaseBuilder()
	{
		return baseBuilder_;
	}

	AppBuilder::AppBuilder(iocServer::construction::IAppBuilder &baseBuilder)
		: baseBuilder_(baseBuilder)
	{
		baseBuilder_.WithFactory<TcpAcceptor, std::tuple<std::shared_ptr<handler::ITcpHandler>, boost::asio::ip::tcp::endpoint &&>, std::tuple<boost::asio::io_context>>();
	}

	IAppBuilder &AppBuilder::WithTcpHandler(
			iocServer::construction::IAppBuilder::IServiceArg<std::shared_ptr<handler::ITcpHandler>> &&handlerFactory,
			boost::asio::ip::tcp::endpoint &&endpoint) {
		baseBuilder_.WithStartableService<TcpAcceptor>(std::move(handlerFactory), iocServer::construction::IAppBuilder::ServiceArgValue<boost::asio::ip::tcp::endpoint &&>(std::move(endpoint)));
		return *this;
	}
}