#pragma once

#include <boost/asio.hpp>

class Request {
    public:
        Request(std::string data, boost::asio::ip::tcp::socket &socket): _data(data), _socket(socket) {}
        ~Request() {}
        std::string _data;
        boost::asio::ip::tcp::socket &_socket;
};