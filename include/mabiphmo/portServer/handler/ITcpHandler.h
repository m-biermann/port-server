//
// Created by max on 8/19/20.
//

#ifndef PORTSERVER_ITCPHANDLER_H
#define PORTSERVER_ITCPHANDLER_H

#include <boost/asio/ip/tcp.hpp>

namespace mabiphmo::portServer::handler {
	class ITcpHandler {
	public:
		virtual void Handle(boost::asio::ip::tcp::socket &&arg) = 0;
	};
}

#endif //PORTSERVER_ITCPHANDLER_H
