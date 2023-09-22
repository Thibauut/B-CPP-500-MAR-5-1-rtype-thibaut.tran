/*
** EPITECH PROJECT, 2023
** client
** File description:
** Client
*/

#pragma once
    #include <iostream>
    #include <boost/asio.hpp>
    #include "../ThreadHandler/ThreadHandler.hpp"

class ClientOpenUDP : public ThreadHandler {
    public:
        ClientOpenUDP(const std::string&);
        void setMessage(const std::string&);
        void run() override;

    private:
        bool sendMessage(const std::string&);
        bool readMessage();
        std::string udpAddress_;
        std::string message_;
        boost::asio::io_service ioService;
        boost::asio::ip::udp::socket socket_;
        boost::asio::ip::udp::endpoint endpoint_;
};
