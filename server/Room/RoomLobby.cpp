/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Room.cpp
*/

#include "RoomLobby.hpp"
#include <atomic>

std::atomic<bool> shouldStop(false);

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
    while (!shouldStop.load(std::memory_order_relaxed)) {
        std::cout << "Room " << _name << " is running" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
    std::cout << "Room " << _name << " stopped" << std::endl;
}

void RoomLobby::stopGame()
{
    shouldStop.store(true, std::memory_order_relaxed);
}

bool RoomLobby::addReadyPlayer()
{
    _nbReadyPlayers++;
    if (_nbReadyPlayers == _nbSlots)
        return (true);
    return (false);
}

std::string RoomLobby::getInfo()
{
    std::string info = "\"" + _name + "\" \"" + std::to_string(_nbPlayers) + "/" + std::to_string(_nbSlots) + "\" \"" + _owner.getUsername() + "\" \"" + std::to_string(_owner.getLevel()) + "\"";
    for (PlayerLobby player : _players) {
        if (player.getUuid() != _owner.getUuid()) {
                info += " \"" + player.getUsername() + "\" \"" + std::to_string(player.getLevel()) + "\"";
        }
    }
    info += "\n";
    return info;
}

bool RoomLobby::addPlayer(PlayerLobby player)
{
    if (_nbPlayers == _nbSlots)
        return (false);
    _players.push_back(player);
    _nbPlayers++;
    return (true);
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
