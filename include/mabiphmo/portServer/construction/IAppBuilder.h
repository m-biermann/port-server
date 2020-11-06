//
// Created by max on 8/17/20.
//

#ifndef PORTSERVER_IAPPBUILDER_H
#define PORTSERVER_IAPPBUILDER_H

#include <utility>
#include <mabiphmo/ioc-server/construction/IAppBuilder.h>
#include <boost/filesystem/path.hpp>
#include <boost/asio/ip/address.hpp>
#include <mabiphmo/portServer/handler/ITcpHandler.h>

namespace mabiphmo::portServer::construction {
	class IAppBuilder {
	public:
		virtual IAppBuilder &WithTcpHandler(std::function<std::shared_ptr<handler::ITcpHandler>()> &&handlerFactory, boost::asio::ip::tcp::endpoint &&endpoint) = 0;

		template<typename THandler>
		IAppBuilder &WithTcpHandler(
				boost::asio::ip::tcp::endpoint &&endpoint) {
			return WithTcpHandler(
				[factory = BaseBuilder().IoCContainer().GetTypeHolder<THandler>()
			        ->template GetFactory<>(),
	                endpoint = std::move(endpoint)]() mutable
                {
					return std::dynamic_pointer_cast<handler::ITcpHandler>((*factory)());
				}, std::move(endpoint));
		}

		virtual ioc_server::construction::IAppBuilder &BaseBuilder() = 0;
	};
}

#endif //PORTSERVER_IAPPBUILDER_H
