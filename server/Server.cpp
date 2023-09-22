/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Server.cpp
*/

#include "Server.hpp"

Server::Server(boost::asio::io_context& io_context, int port) : _menu(io_context), _port(port) { initServer();}

Server::~Server() {}

void Server::initServer() {}

void Server::run(boost::asio::io_context &context)
{
     try {
        std::thread refresh_thread(&Server::refresh, this);
        context.run();
        refresh_thread.join();
    } catch (std::exception &e) {}
}

void Server::refresh()
{
    // PlayerLobby player = PlayerLobby("Tbz");
    // RoomLobby lobby = RoomLobby(player, 4, "le galion");
    // lobby.startGame();
    while (1) {
        _menu.getAllTcpRequest();
    }
}

void Server::createRoom(PlayerLobby owner, std::string name, int _nbSlots)
{
    _lobbys.push_back(RoomLobby(owner, _nbSlots, name));
}

void Server::addClientToRoom(int pos, PlayerLobby client)
{
    _lobbys.at(pos).addPlayer(client);
}

void Server::deleteRoom(int pos)
{
    _lobbys.erase(_lobbys.begin() + pos);
}