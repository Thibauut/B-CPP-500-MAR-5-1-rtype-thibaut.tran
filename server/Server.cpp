/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Server.cpp
*/

#include "Server.hpp"

Server::Server(int port) : _menu(_service, port), _port(port) { initServer(); }

Server::~Server() {}

void Server::initServer()
{
    _menu.start();
    _menu.handleClient();
}

void Server::run()
{
    while (1) {
        
    }
}

void Server::createRoom()
{
    // _lobbys.push_back(UDPSocket(_service, _port));
}

void Server::addClientToRoom(int pos, int client)
{
    // _lobbys[pos].addClient(client);
}

void Server::deleteRoom(int pos)
{
    // _lobbys.erase(_lobbys.begin() + pos);
}
