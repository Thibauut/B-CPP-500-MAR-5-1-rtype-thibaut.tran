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
        void stopGame();
        void addPlayer(PlayerLobby player);
        void removePlayer(std::string uid);
        std::string getInfo();
        void addReadyPlayer();

        std::string getName() const { return _name; }
        unsigned int getNbSlots() const { return _nbSlots; }
        unsigned int getNbPlayers() const { return _nbPlayers; }
        PlayerLobby getOwner() const { return _owner; }
        std::vector<PlayerLobby> getPlayers() const { return _players; }
        std::string getUuid() const { return _uuid; }
        unsigned int getNbReadyPlayers() const { return _nbReadyPlayers; }

    private:
        void gameEntryPoint();

        std::string _uuid;
        std::string _name;
        unsigned int _nbSlots;
        unsigned int _nbPlayers;
        unsigned int _nbReadyPlayers;
        PlayerLobby _owner;

        std::vector<PlayerLobby> _players;
        std::thread _thread;
};