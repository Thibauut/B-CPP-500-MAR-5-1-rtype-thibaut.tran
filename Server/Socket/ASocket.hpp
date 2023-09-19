// /*
// ** EPITECH PROJECT, 2023
// ** B-CPP-500-MAR-5-1-rtype-maori.dino
// ** File description:
// ** ASocket.hpp
// */

// #pragma once

// #include "ISocket.hpp"
// #include <boost/asio.hpp>
// #include <boost/array.hpp>

// class ASocket : public ISocket {
//     public:
//         ASocket() {};
//         ASocket(ASocket &socket) {
//             // _port = socket._port;
//             // _service = socket._service;
//             // _buffer = socket._buffer;
//             // _acceptor = socket._acceptor;
//             // _socket = socket._socket;
//         }

//         ASocket(boost::asio::io_service& ioService, int port);
//         virtual ~ASocket() = default;
//         virtual void send(const std::string &message) {};
//         virtual std::string receive() {};
//         virtual void acceptSocket() {};
//         virtual void closeSocket() {};
//         virtual void start() {};
//         virtual void handleClient() {};

//         // Setters


//         // Getters
//         virtual int getPort() const { return _port; };
//         virtual boost::asio::io_service &getService() { return _service; };
//         virtual boost::asio::streambuf &getBuffer() { return _buffer; };
//         virtual boost::asio::ip::tcp::acceptor &getAcceptor() { return _acceptor; };
//         virtual boost::asio::ip::tcp::socket &getSocket() { return _socket; };

//     private:
//         int _port;
//         boost::asio::io_service &_service;
//         boost::asio::streambuf _buffer;
//         boost::asio::ip::tcp::acceptor _acceptor;
//         boost::asio::ip::tcp::socket _socket;
// };