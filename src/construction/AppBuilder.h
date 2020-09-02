//
// Created by max on 8/18/20.
//

#ifndef TCPSERVER_APPBUILDER_H
#define TCPSERVER_APPBUILDER_H

#include <mabiphmo/portServer/construction/IAppBuilder.h>
#include <mabiphmo/iocServer/construction/IAppBuilder.h>

namespace mabiphmo::portServer::construction {
	class AppBuilder : public IAppBuilder {
		iocServer::construction::IAppBuilder &baseBuilder_;
	protected:
		iocServer::construction::IAppBuilder &BaseBuilder() override;
	public:
		explicit AppBuilder(iocServer::construction::IAppBuilder &baseBuilder);
		IAppBuilder &WithTcpHandler(iocServer::construction::IAppBuilder::IServiceArg<std::shared_ptr<handler::ITcpHandler>> &&handlerFactory, boost::asio::ip::tcp::endpoint &&endpoint) override;
	};
}

#endif //TCPSERVER_APPBUILDER_H
