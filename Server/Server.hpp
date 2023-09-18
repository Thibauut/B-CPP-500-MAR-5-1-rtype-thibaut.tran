/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Server.hpp
*/

#pragma once
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "Socket/ISocket.hpp"
#include <vector>


class Server {
    public:
        Server();
        ~Server();
        void init_server();

    private:
        ISocket *menu;
        std::vector <ISocket *> lobby;
        // std::vector<*ISocket> _game;
};