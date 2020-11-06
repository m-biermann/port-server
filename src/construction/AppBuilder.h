//
// Created by max on 8/18/20.
//

#ifndef TCPSERVER_APPBUILDER_H
#define TCPSERVER_APPBUILDER_H

#include <mabiphmo/portServer/construction/IAppBuilder.h>
#include <mabiphmo/ioc-server/construction/IAppBuilder.h>

namespace mabiphmo::portServer::construction {
	class AppBuilder : public IAppBuilder {
		ioc_server::construction::IAppBuilder &baseBuilder_;
	protected:
		ioc_server::construction::IAppBuilder &BaseBuilder() override;
	public:
		explicit AppBuilder(ioc_server::construction::IAppBuilder &baseBuilder);
		IAppBuilder &WithTcpHandler(std::function<std::shared_ptr<handler::ITcpHandler>()> &&handlerFactory, boost::asio::ip::tcp::endpoint &&endpoint) override;
	};
}

#endif //TCPSERVER_APPBUILDER_H
