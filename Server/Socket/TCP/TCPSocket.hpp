/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** TCPSocket.hpp
*/

#pragma once
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>

using namespace boost::asio::ip;
using namespace std;

class TCPSocket {
    public:
        TCPSocket(boost::asio::io_service& ioService, int port);
        ~TCPSocket() = default;

        void acceptSocket();
        void start();
        void handleClient();

    private:
        int _port;
        boost::asio::io_service &_service;
        boost::asio::streambuf _buffer;
        tcp::acceptor _acceptor;
        tcp::socket _socket;
};

        // virtual void send(const std::string &message) {};
        // virtual std::string receive() {};
        // virtual void bindSocket() {};
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