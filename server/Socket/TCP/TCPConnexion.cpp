/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** TCPConnexion.cpp
*/

#include "TCPConnexion.hpp"

void TCPConnexion::start() {
    _message = "Bienvenue sur Hess-Type jeune joueur !";
    boost::asio::async_write(
        _socket, boost::asio::buffer(_message),
        boost::bind(&TCPConnexion::handle_write, this,
        boost::asio::placeholders::error
    ));
};

void TCPConnexion::do_read() {
    // auto self(shared_from_this());
    // _socket.async_read_some(boost::asio::buffer(_data, max_length),
    //     [this, self](boost::system::error_code ec, std::size_t length) {
    //         if (!ec) {
    //             std::cout << "Message reçu: ";
    //             std::cout << _data << "." <<std::endl;
    //             do_read();
    //         }
    //     });
    boost::asio::async_read(_socket, boost::asio::buffer(_buffer),
        boost::bind(&TCPConnexion::handle_read, this,
        boost::asio::placeholders::error)
    );
}

void TCPConnexion::handle_read(const boost::system::error_code& error) {
    if (!error) {
        std::cout << "Message reçu : ";
        std::cout << _buffer.at(0) << std::endl;
        do_read();
    } else {
        std::cerr << "Error at handle_read: " << error.message() << std::endl;
        _socket.close();
    }
};

// void TCPConnexion::close() {
//     _socket.close();
// };

void TCPConnexion::handle_write(const boost::system::error_code& error) {
    if (!error) {
        std::cout << "Message sent" << std::endl;
        do_read();
    } else {
        cerr << "Error at handle_write: " << error.message() << endl;
        _socket.close();
    }
};