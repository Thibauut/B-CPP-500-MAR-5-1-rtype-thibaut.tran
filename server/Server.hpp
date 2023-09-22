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
// #include <thread>
#include "Socket/TCP/TCPServer.hpp"
#include "Room/RoomLobby.hpp"

class Server {
    public:
        Server(boost::asio::io_context& io_context, int port);
        ~Server();
        void initServer();
        void run(boost::asio::io_context &context);
        void refresh();
        void createRoom(PlayerLobby owner, std::string name, int _nbSlots);
        void addClientToRoom(int pos, PlayerLobby client);
        void deleteRoom(int pos);
    private:
        TCPServer _menu;
        int _port;
        std::vector <RoomLobby> _lobbys;
};