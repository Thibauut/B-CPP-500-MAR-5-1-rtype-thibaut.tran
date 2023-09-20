/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** TCPServer.hpp
*/

#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include "TCPConnexion.hpp"

using boost::asio::ip::tcp;
using namespace std;

class TCPServer {
	public:
		TCPServer(boost::asio::io_service& io_service, int port)
			: m_acceptor(io_service, tcp::endpoint(tcp::v4(), port)), _service(io_service)
		{
			start_accept();
		}

	private:
		void start_accept()
		{
			new_connection = TCPConnexion::create_new_connection(_service);

			m_acceptor.async_accept(new_connection->socket(),
				boost::bind(&TCPServer::handle_accept, this, new_connection,
				boost::asio::placeholders::error));
		}

	void handle_accept(TCPConnexion::pointer new_connection, const boost::system::error_code& error) // (4)
	{
		if (!error)
		{
			std::cout << "Reçu un clin's!" << std::endl;
			new_connection->start();
			start_accept();
		}
	}

	TCPConnexion::pointer new_connection;
	tcp::acceptor m_acceptor;
	boost::asio::io_service &_service;
};