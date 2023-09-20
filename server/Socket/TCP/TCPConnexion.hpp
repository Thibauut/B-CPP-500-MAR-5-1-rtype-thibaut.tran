/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** TCPConnexion.hpp
*/

#pragma once
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/array.hpp>
#include <iostream>

using namespace std;

class TCPConnexion : public enable_shared_from_this<TCPConnexion> {
    public:
        typedef boost::shared_ptr<TCPConnexion> pointer;
        static pointer create_new_connection(boost::asio::io_service& service) {return pointer(new TCPConnexion(service));}
        boost::asio::ip::tcp::socket& socket() { return _socket;};
        void start();
        void do_read();
        // void do_write(std::size_t length);
        ~TCPConnexion() {};

    private:
        TCPConnexion(boost::asio::io_service& ioService) : _socket(ioService) {}
        // void close();
        void handle_read(const boost::system::error_code& error);
        void handle_write(const boost::system::error_code& error);

        std::string _message;
        // boost::asio::deadline_timer cooldown_timer;
        boost::asio::ip::tcp::socket _socket;
        // std::string _buffer2;
        boost::array<char, 1024> _buffer;
        // enum { max_length = 1024 };
        // char _data[max_length];
};