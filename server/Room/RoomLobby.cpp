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
    _nbReadyPlayers = 0;
    _thread = std::thread(&RoomLobby::gameEntryPoint, this);
}

RoomLobby::~RoomLobby() {
    if (_thread.joinable())
        _thread.join();
}
void RoomLobby::startGame()
{
    // try {
    //     _thread = std::thread(&RoomLobby::gameEntryPoint, this);
    // } catch (std::exception &e) {
    //     std::cerr << e.what() << std::endl;
    // }
}

void RoomLobby::gameEntryPoint()
{
    std::cout << "Room " << _name << " started" << std::endl;
    while (true) {
        if (_nbPlayers <= 0)
            _thread.join();
        std::cout << "Room " << _name << " is running" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
    std::cout << "Room " << _name << " stopped" << std::endl;
}

void RoomLobby::stopGame()
{
    _thread.join();
}

void RoomLobby::addReadyPlayer()
{
    _nbReadyPlayers++;
}

std::string RoomLobby::getInfo()
{
    std::string info = "\"" + _name + "\" \"" + std::to_string(_nbPlayers) + "/" + std::to_string(_nbSlots) + "\" \"" + _owner.getUsername() + "\"\n";
    for (PlayerLobby player : _players) {
        if (player.getUuid() != _owner.getUuid()) {
            if (player.getUuid() != _players.back().getUuid())
                info += "\"" + player.getUsername() + "\" \"" + std::to_string(player.getLevel()) + "\" ";
            else
                info += "\"" + player.getUsername() + "\" \"" + std::to_string(player.getLevel()) + "\"\n";
        }
    }
    return info;
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
