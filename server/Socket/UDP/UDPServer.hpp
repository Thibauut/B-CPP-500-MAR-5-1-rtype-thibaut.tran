#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <list>
using boost::asio::ip::udp;

class UDPRequest {
    public:
        UDPRequest(std::string data, udp::endpoint &client): data_(data), client_(client) {}
        ~UDPRequest() {}
        std::string data_;
        udp::endpoint &client_;
};

class UDPServer {
public:
    UDPServer(boost::asio::io_service& io_service, unsigned short port);
    void StartReceive();
    void StartSend(const std::string& message);
    udp::socket &Socket(){return socket_;}
    // ------------CMD--------------
    void SendAllPlayersPosition();
    void SendAllProjectilsPosition();
    void SendAllPnjPosition();
    void SendAllCollectiblePosition();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void Shoot();
    void sendScores();

private:
    udp::endpoint remote_endpoint_;
    std::vector<char> recv_buf_;
    udp::socket socket_;
};