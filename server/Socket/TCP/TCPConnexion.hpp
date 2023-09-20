/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** TCPConnexion.hpp
*/

#pragma once
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
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
            _message = "Salut pd";
            boost::asio::async_write(_socket, boost::asio::buffer(_message),
                boost::bind(&TCPConnexion::handle_write, this,
                    boost::asio::placeholders::error
            ));
        };

        ~TCPConnexion() {};

    private:
        void handle_write(const boost::system::error_code& error) {
            if (!error) {
                cout << "Message sent" << endl;
            } else {
                cerr << "Error: " << error.message() << endl;
                _socket.close();
            }
        };

        std::string _message;
        boost::asio::ip::tcp::socket _socket;
};