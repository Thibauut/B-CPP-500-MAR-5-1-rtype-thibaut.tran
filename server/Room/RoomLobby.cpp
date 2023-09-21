/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Room.cpp
*/

#include "RoomLobby.hpp"

RoomLobby::RoomLobby(PlayerLobby &owner, unsigned int nbSlots, std::string name) : _owner(owner)
{
    _players.push_back(owner);
    _nbPlayers = 1;
    _nbSlots = nbSlots;
    _name = name;
    _thread.setStatus(STARTED);
    _thread.create((void *(*)(void *)) &gameThread, this);
}

RoomLobby::~RoomLobby() {
    _thread.setStatus(STOPPED);
    _thread.join();
}

void RoomLobby::join()
{
    _thread.join();
}

void RoomLobby::startGame()
{
    _thread.setStatus(RUNNING);
}

void RoomLobby::addPlayer(PlayerLobby player)
{
    _players.push_back(player);
    _nbPlayers++;
}

void RoomLobby::removePlayer(std::string uid)
{
    for (int i = 0; i < _players.size(); i++) {
        if (_players[i].getUid() == uid) {
            _players.erase(_players.begin() + i);
            _nbPlayers--;
        }
    }
}
