//
// Created by max on 8/24/20.
//

#include "TcpAcceptor.h"
#include <boost/asio/dispatch.hpp>

namespace mabiphmo::portServer {
	void TcpAcceptor::onStart()
	{
		doAccept();
	}

	void TcpAcceptor::onStop() {}

	void TcpAcceptor::doAccept() {
		{
			const std::lock_guard<std::mutex> lock(runningMutex_);
			if(!running_)
				return;
		}
		acceptor_.async_accept(boost::asio::make_strand(*ioContext_), [capture0 = shared_from_this()](const boost::system::error_code &ec, boost::asio::ip::tcp::socket socket) { capture0->onAccept(ec, std::move(socket)); });
	}

	void TcpAcceptor::onAccept(const boost::system::error_code &ec, boost::asio::ip::tcp::socket &&socket) {
		if (ec) {
			std::cerr << "accept failed: " << ec.message() << std::endl;
		} else {
			boost::asio::dispatch(socket.get_executor(), [this, socket = std::move(socket)] () mutable {handler_->Handle(std::move(socket));});
		}

		doAccept();
	}

	TcpAcceptor::TcpAcceptor(std::shared_ptr<boost::asio::io_context> ioContext,
	                         std::shared_ptr<handler::ITcpHandler> handler, boost::asio::ip::tcp::endpoint &&endpoint)
			: ioContext_(std::move(ioContext)),
			  handler_(std::move(handler)),
			  acceptor_(*ioContext_)
	{
		boost::system::error_code ec;

		acceptor_.open(endpoint.protocol(), ec);
		if(ec){
			std::stringstream ss;
			ss << "open failed: " << ec.message();
			throw AcceptorException(ss.str());
		}

		acceptor_.set_option(boost::asio::socket_base::reuse_address(true), ec);
		if(ec){
			std::stringstream ss;
			ss << "address reuse failed: " << ec.message();
			throw AcceptorException(ss.str());
		}

		acceptor_.bind(endpoint, ec);
		if(ec){
			std::stringstream ss;
			ss << "bind failed: " << ec.message();
			throw AcceptorException(ss.str());
		}

		acceptor_.listen(boost::asio::socket_base::max_listen_connections, ec);
		if(ec){
			std::stringstream ss;
			ss << "listen failed: " << ec.message();
			throw AcceptorException(ss.str());
		}
	}
}