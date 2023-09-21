/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Server.hpp
*/

#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <vector>
#include "Socket/TCP/TCPServer.hpp"
#include "Room/RoomLobby.hpp"

class Server {
    public:
        Server(boost::asio::io_context& io_context, int port);
        ~Server();
        void initServer();
        void run();

        // Room
        void createRoom(std::string name, int nbSlots, std::string uid_owner);
        bool deleteRoom(std::string uid_room);
        bool addPlayerToRoom(std::string uid_room, std::string uid_player);
        bool removePlayerFromRoom(std::string uid_room, std::string uid_player);
        bool startGame(std::string uid_room);

    private:
        TCPServer _tcp_server;
        std::vector<RoomLobby> _rooms;
        int _port;
};