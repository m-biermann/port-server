//
// Created by max on 8/17/20.
//

#ifndef HTTPSERVER_IAPPBUILDER_H
#define HTTPSERVER_IAPPBUILDER_H

#include <utility>
#include <mabiphmo/iocServer/construction/IAppBuilder.h>
#include <boost/filesystem/path.hpp>
#include <boost/asio/ip/address.hpp>
#include <mabiphmo/portServer/handler/ITcpHandler.h>

namespace mabiphmo::portServer::construction {
	class IAppBuilder {
	public:
		virtual IAppBuilder &WithTcpHandler(std::unique_ptr<iocServer::construction::IServiceArg<std::shared_ptr<handler::ITcpHandler>>> &&handlerFactory, boost::asio::ip::tcp::endpoint &&endpoint) = 0;

		virtual iocServer::construction::IAppBuilder &BaseBuilder() = 0;
	};
}

#endif //HTTPSERVER_IAPPBUILDER_H
