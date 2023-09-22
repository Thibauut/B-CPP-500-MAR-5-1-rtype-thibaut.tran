/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** RoomLobby.hpp
*/

#pragma once
#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include "../Elements/Player/PlayerLobby.hpp"

class RoomLobby {
    public:
        RoomLobby(PlayerLobby owner, unsigned int nbSlots, std::string name, std::string uuid);
        ~RoomLobby();

        void startGame();
        void addPlayer(PlayerLobby player);
        void removePlayer(std::string uid);
        void gameEntryPoint();

        std::string getName() const { return _name; }
        unsigned int getNbSlots() const { return _nbSlots; }
        unsigned int getNbPlayers() const { return _nbPlayers; }
        PlayerLobby getOwner() const { return _owner; }
        std::vector<PlayerLobby> getPlayers() const { return _players; }
        std::string getUuid() const { return _uuid; }

        std::string _uuid;
        std::string _name;
        unsigned int _nbSlots;
        unsigned int _nbPlayers;
        PlayerLobby _owner;
        std::vector<PlayerLobby> _players;
};