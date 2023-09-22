/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Room.cpp
*/

#include "RoomLobby.hpp"

RoomLobby::RoomLobby(PlayerLobby owner, unsigned int nbSlots, std::string name, std::string uuid) : _owner(owner)
{
    _players.push_back(owner);
    _nbPlayers = 1;
    _nbSlots = nbSlots;
    _name = name;
    _uuid = uuid;
}

RoomLobby::~RoomLobby() {
}
void RoomLobby::startGame()
{
    try {
        std::thread room_game(&RoomLobby::gameEntryPoint, this);
        room_game.join();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void RoomLobby::gameEntryPoint()
{
    std::cout << "Room " << _name << " started" << std::endl;
    while (true) {
        std::cout << "Room " << _name << " running" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    std::cout << "Room " << _name << " stopped" << std::endl;
}

void RoomLobby::addPlayer(PlayerLobby player)
{
    _players.push_back(player);
    _nbPlayers++;
}

void RoomLobby::removePlayer(std::string uid)
{
    for (int i = 0; i < _players.size(); i++) {
        if (_players[i].getUuid() == uid) {
            _players.erase(_players.begin() + i);
            _nbPlayers--;
        }
    }
}
