//
// Created by max on 8/18/20.
//

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <mabiphmo/iocServer/construction/ServiceArgValue.h>
#include "AppBuilder.h"
#include "../TcpAcceptor.h"

using namespace mabiphmo::iocServer::construction;

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
			std::unique_ptr<iocServer::construction::IServiceArg<std::shared_ptr<handler::ITcpHandler>>> &&handlerFactory,
			boost::asio::ip::tcp::endpoint &&endpoint) {
		baseBuilder_.WithStartableService(
			baseBuilder_.ServiceArgBaseRelationFactory<iocServer::service::IStartableService, TcpAcceptor>(
				std::move(handlerFactory),
				std::unique_ptr<IServiceArg<boost::asio::ip::tcp::endpoint &&>>(
					new ServiceArgValue<boost::asio::ip::tcp::endpoint &&>(
						std::move(endpoint)))));
		return *this;
	}
}