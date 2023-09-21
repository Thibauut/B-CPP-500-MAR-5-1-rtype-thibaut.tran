/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Server.cpp
*/

#include "Server.hpp"

Server::Server(boost::asio::io_context& io_context, int port) : _tcp_server(io_context), _port(port) { initServer();}

Server::~Server() {}

void Server::initServer(){}

void Server::run()
{
    while (1) {
        // cout <<"le while (1)"<< endl;
    }
}

void Server::createRoom(std::string name, int nbSlots, std::string uid_owner)
{
    _rooms.push_back(RoomLobby(_tcp_server.getPlayerByUid(uid_owner), nbSlots, name));
}

bool Server::addPlayerToRoom(std::string uid_room, std::string uid_player)
{
    int pos = 0;
    for (int i = 0; i < _rooms.size(); i++)
        if (_rooms.at(i).getUid() == uid_room)
            pos = i;
    if (_rooms.at(pos).getNbPlayers() >= _rooms.at(pos).getNbSlots())
        return (false);
    _rooms.at(pos).addPlayer(_tcp_server.getPlayerByUid(uid_player));
    return (true);
}

bool Server::deleteRoom(std::string uid_room)
{
    for (int i = 0; i < _rooms.size(); i++) {
        if (_rooms.at(i).getUid() == uid_room) {
            _rooms.erase(_rooms.begin() + i);
            return (true);
        }
    }
    return (false);
}

bool Server::removePlayerFromRoom(std::string uid_room, std::string uid_player)
{
    int pos = 0;
    for (int i = 0; i < _rooms.size(); i++)
        if (_rooms.at(i).getUid() == uid_room)
            pos = i;
    _rooms.at(pos).removePlayer(uid_player);
    return (true);
}

bool Server::startGame(std::string uid_room)
{
    int pos = 0;
    for (int i = 0; i < _rooms.size(); i++)
        if (_rooms.at(i).getUid() == uid_room)
            pos = i;
    _rooms.at(pos).startGame();
    return (true);
}
