/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** TCPSocket.hpp
*/

#pragma once
#include "../ASocket.hpp"
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>

class TCPSocket : public ASocket {
    public:
        TCPSocket();
        virtual ~TCPSocket() = default;
using boost::asio::ip::tcp;
        int port;
        boost::asio::io_service& _ioService;
        boost::asio::ip::tcp::acceptor _acceptor;
        boost::asio::ip::tcp::socket _socket;
        boost::asio::streambuf _buffer;


    private:
};

        // virtual void send(const std::string &message) {};
        // virtual std::string receive() {};
        // virtual void bindSocket() {};
        // virtual void connectSocket() {};
        // virtual void closeSocket() {};
        // virtual void setPort(const int &port) {};
        // virtual int getPort() {};
        // virtual void setIp(const std::string &ip) {};
        // virtual std::string getIp() {};
        // virtual std::string getProtocol() const {};
        // virtual void setSocketType(const std::string &socketType) {};
        // virtual std::string getSocketType() const {};
        // virtual void setSocket(const int &socket) {};
        // virtual int getSocket() const {};
        // virtual void setAddr(const struct sockaddr_in &addr) {};
        // virtual struct sockaddr_in getAddr() const {};
        // virtual void setAddrLen(const socklen_t &addrLen) {};
        // virtual socklen_t getAddrLen() const {};