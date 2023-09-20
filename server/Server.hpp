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

class Server {
    public:
        Server(boost::asio::io_context& io_context, int port);
        ~Server();
        void initServer();
        void run();
        void createRoom();
        void addClientToRoom(int pos, int client);
        void deleteRoom(int pos);
    private:
        TCPServer _menu;
        int _port;
        // std::vector <UDPSocket *> _lobbys;
};