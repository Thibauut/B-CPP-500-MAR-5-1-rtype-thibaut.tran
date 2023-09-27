/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Room.cpp
*/

#pragma once
#include "Room.hpp"
#include "RoomLobby.hpp"

void gameThread(void *arg)
{
    std::cout << "Room started" << std::endl;
    RoomLobby *roomLobby = (RoomLobby *)arg;
    // Room room = Room(roomLobby->getName(), roomLobby->getOwner().getUuid(), roomLobby->getNbSlots());
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

Room::Room(std::string name, std::string owner, unsigned int nbSlots)
{
    _name = name;
    _owner_uid = owner;
    _nbSlots = nbSlots;
    _nbPlayers = 1;
}

