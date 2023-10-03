#pragma once

#include <boost/asio.hpp>
#include <boost/uuid/uuid_io.hpp>

class Request {
    public:
        Request(std::string data, boost::asio::ip::tcp::socket &socket, boost::uuids::uuid uuid): _data(data), _socket(socket), _uuid(uuid) {}
        ~Request() {}

        std::string _data;
        boost::asio::ip::tcp::socket &_socket;
        boost::uuids::uuid _uuid;
};
