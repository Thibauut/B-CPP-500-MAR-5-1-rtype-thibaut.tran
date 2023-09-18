/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** ISocket.hpp
*/

#pragma once
#include <string>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <boost/asio.hpp>

class ISocket {
    public:
        virtual ~ISocket() = default;
        virtual void send(const std::string &message) = 0;
        virtual std::string receive() = 0;
        virtual void bindSocket() = 0;
        virtual void connectSocket() = 0;
        virtual void closeSocket() = 0;
        virtual void setPort(const int &port) = 0;
        virtual void setIp(const std::string &ip) = 0;
        virtual std::string getIp() const = 0;
        virtual std::string getProtocol() const = 0;
        virtual void setSocketType(const std::string &socketType) = 0;
        virtual std::string getSocketType() const = 0;
        virtual void setSocket(const int &socket) = 0;
        virtual int getSocket() const = 0;
        virtual void setAddr(const struct sockaddr_in &addr) = 0;
        virtual struct sockaddr_in getAddr() const = 0;
        virtual void setAddrLen(const socklen_t &addrLen) = 0;
        virtual socklen_t getAddrLen() const = 0;

};