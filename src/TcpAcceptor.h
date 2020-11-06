//
// Created by max on 8/22/20.
//

#ifndef PORTSERVER_TCPACCEPTOR_H
#define PORTSERVER_TCPACCEPTOR_H

#include <type_traits>
#include <mabiphmo/portServer/handler/ITcpHandler.h>
#include <boost/asio/ip/tcp.hpp>
#include <mabiphmo/ioc-server/service/IStartableService.h>
#include <boost/asio/strand.hpp>
#include <iostream>

namespace mabiphmo::portServer {
	class AcceptorException : public std::runtime_error {
	public:
		explicit AcceptorException(
			const std::string &message)
			: std::runtime_error(message) {}
		AcceptorException() : AcceptorException("") {}
	};

	class TcpAcceptor : public ioc_server::service::IStartableService, std::enable_shared_from_this<TcpAcceptor>
	{
		std::shared_ptr<boost::asio::io_context> ioContext_;
		std::shared_ptr<handler::ITcpHandler> handler_;
		boost::asio::ip::tcp::acceptor acceptor_;

		void doAccept();
		void onAccept(const boost::system::error_code &ec, boost::asio::ip::tcp::socket &&socket);
	protected:
		void onStart() override;
		void onStop() override;
	public:
		TcpAcceptor(
			std::shared_ptr<boost::asio::io_context> ioContext,
			std::shared_ptr<handler::ITcpHandler> handler,
			boost::asio::ip::tcp::endpoint &&endpoint);
	};
}

#endif //PORTSERVER_TCPACCEPTOR_H
