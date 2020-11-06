//
// Created by max on 8/18/20.
//

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include "AppBuilder.h"
#include "../TcpAcceptor.h"

using namespace mabiphmo::ioc_server::construction;

namespace mabiphmo::portServer::construction {
	ioc_server::construction::IAppBuilder &AppBuilder::BaseBuilder()
	{
		return baseBuilder_;
	}

	AppBuilder::AppBuilder(ioc_server::construction::IAppBuilder &baseBuilder)
		: baseBuilder_(baseBuilder)
	{
		baseBuilder_.IoCContainer().RegisterType(
			ioc_container::TypeHolder<TcpAcceptor>(
				ioc_container::Scope::Factory,
				std::function<std::shared_ptr<TcpAcceptor>(std::shared_ptr<handler::ITcpHandler>, boost::asio::ip::tcp::endpoint &&)>(
					[&ioc = baseBuilder_.IoCContainer()](
						const std::shared_ptr<handler::ITcpHandler>& handler,
				        boost::asio::ip::tcp::endpoint &&endpoint)
					{
						return std::make_shared<TcpAcceptor>(
							ioc.GetTypeHolder<boost::asio::io_context>()->Get(),
							handler, std::move(endpoint));
					})));
	}

	IAppBuilder &AppBuilder::WithTcpHandler(
			std::function<std::shared_ptr<handler::ITcpHandler>()> &&handlerFactory,
			boost::asio::ip::tcp::endpoint &&endpoint) {
		baseBuilder_.WithStartableService(
			[endpoint = std::move(endpoint),
				handler = std::move(handlerFactory),
				parametrizedFactory = baseBuilder_.IoCContainer().GetTypeHolder<TcpAcceptor>()->
					GetFactory<std::shared_ptr<handler::ITcpHandler>,
					boost::asio::ip::tcp::endpoint &&>()]() mutable
			{
				return std::dynamic_pointer_cast<ioc_server::service::IStartableService>((*parametrizedFactory)(handler(), std::move(endpoint)));
			});
		return *this;
	}
}