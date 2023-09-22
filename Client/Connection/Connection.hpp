/*
** EPITECH PROJECT, 2023
** client
** File description:
** Client
*/

#pragma once

#include <iostream>
#include <boost/asio.hpp>

class ClientConnection {
public:
    ClientConnection(const std::string&, const std::string&, const std::string&);
    bool sendMessage(const std::string&);
    bool readMessage(const std::string&);

private:
    std::string ip_;
    std::string port_;
    std::string username_;
    boost::asio::io_service ioService; // Ajout de ioService pour initialiser socket_
    boost::asio::ip::tcp::socket socket_;
};