/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** TCPConnexion.hpp
*/

#pragma once
#include <boost/asio.hpp>
#include <iostream>

using namespace std;

class TCPConnexion : public enable_shared_from_this<TCPConnexion> {
    public:
        typedef boost::shared_ptr<TCPConnexion> pointer;
        TCPConnexion(boost::asio::io_service& ioService) : _socket(ioService){}
        static pointer create_new_connection(boost::asio::io_service& service) {
            return pointer(new TCPConnexion(service));
        }
        boost::asio::ip::tcp::socket& socket() { return _socket;};

        void start() {
        };

        ~TCPConnexion() {};
    private:
        std::string _message;
        boost::asio::ip::tcp::socket _socket;
};