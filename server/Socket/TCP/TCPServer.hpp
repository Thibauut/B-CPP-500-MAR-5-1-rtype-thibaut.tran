/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** TCPServer.hpp
*/

#pragma once
#include <boost/asio.hpp>
#include "TCPConnexion.hpp"

class TCPServer
{
public:
  TCPServer(boost::asio::io_context& io_context);

private:
  void start_accept();
  void handle_accept(TCPConnection::pointer new_connection, const boost::system::error_code& error);

  boost::asio::io_context& io_context_;
  boost::asio::ip::tcp::acceptor acceptor_;
};