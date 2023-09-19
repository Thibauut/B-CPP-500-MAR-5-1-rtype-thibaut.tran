/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** TCPSocket.cpp
*/

#include "TCPSocket.hpp"

TCPSocket::TCPSocket(boost::asio::io_service& ioService, int port)
    : _port(port), _service(ioService), _acceptor(ioService,  boost::asio::ip::tcp::endpoint( boost::asio::ip::tcp::v4(), port)), _socket(ioService)
{
    acceptSocket();
}

void TCPSocket::acceptSocket()
{
    _acceptor.async_accept(_socket, [this](const boost::system::error_code& ec) {
        if (!ec) {
            cout << "Client connected"<< endl;
            _socket.send(boost::asio::buffer("Welcome to Hess-Type Server !\n"));
        }
        acceptSocket();
    });
}

void TCPSocket::start()
{
    _service.run();
}

void TCPSocket::handleClient()
{
    boost::asio::async_read_until(_socket, _buffer, '\n', [this](const boost::system::error_code& ec, size_t bytes_transferred) {
        if (!ec) {
            istream input_stream(&_buffer);
            string message;
            getline(input_stream, message);
            cout << "Message du client : " << message << endl;
            handleClient();
        }
    });
}