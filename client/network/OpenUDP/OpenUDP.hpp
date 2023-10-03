/*
** EPITECH PROJECT, 2023
** client
** File description:
** Client
*/

#pragma once
    #include <iostream>
    #include <boost/asio.hpp>
    #include <boost/array.hpp>
    #include "../ThreadHandler/ThreadHandler.hpp"
    #include "../../include/player.hpp"

class ClientOpenUDP : public ThreadHandler {
    public:
        ClientOpenUDP(const std::string& serverIp, const std::string& serverPort, std::vector<std::shared_ptr<PlayerUDP>> &players, const std::string my_id);
        void setMessage(const std::string&);
        void run() override;

        bool sendMessageSync(const std::string&);
        bool sendMessageSyncFirst(const std::string&);

        bool readMessage();
        bool readPositionFirst();
        bool getRunning() override;
        bool getPLayersPos(const std::string& msg);
        bool readPos();

        std::string ipAddress_;
        std::string udpPort_;
        std::string udpAddress_;
        std::string message_;
        std::string my_id_;

        boost::array<char, 128>  buffer_;
        boost::asio::io_context ioService;
        boost::asio::ip::udp::socket socket_;
        boost::asio::ip::udp::endpoint endpoint_;
        std::vector<std::shared_ptr<PlayerUDP>> &players_;
};
