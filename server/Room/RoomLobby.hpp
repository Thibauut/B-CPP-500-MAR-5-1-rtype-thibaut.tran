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
#include "../Socket/UDP/UDPServer.hpp"
#include "../../GameEngine/GameEngine.hpp"
#include "../Elements/Map/Map.hpp"
class RoomLobby {
    public:
        RoomLobby(std::shared_ptr<PlayerLobby> owner, unsigned int nbSlots, std::string name, std::string uuid, std::string pathMap, int gameType);
        ~RoomLobby();

        void startGame();
        void stopGame();
        bool addPlayer(std::shared_ptr<PlayerLobby> player);
        void removePlayer(std::string uid);
        std::string getInfo();
        bool addReadyPlayer();

        std::string getName() const { return _name; }
        unsigned short getPort() const { return _port; }
        unsigned int getNbSlots() const { return _nbSlots; }
        unsigned int getNbPlayers() const { return _nbPlayers; }
        std::shared_ptr<PlayerLobby> getOwner() const { return _owner; }
        std::vector<std::shared_ptr<PlayerLobby>>&  getPlayers() { return _players; }
        std::string getUuid() const { return _uuid; }
        unsigned int getNbReadyPlayers() const { return _nbReadyPlayers; }
        bool isStarted() const { return _isStarted; }
        void setStarted(bool started) { _isStarted = started; }

    private:
        void gameEntryPoint();
        void PvpEntryPoint();
        void BattleRoyalEntryPoint();
        void DuoPvpEntryPoint();
        void SurvivalEntryPoint();
        unsigned short _port;
        std::string _uuid;
        std::string _name;
        std::string _pathMap;
        unsigned int _nbSlots;
        unsigned int _nbPlayers;
        unsigned int _nbReadyPlayers;
        int _gameType;
        std::shared_ptr<PlayerLobby> _owner;
        std::vector<std::shared_ptr<PlayerLobby>> _players;
        std::thread _thread;
        bool _isStarted;
};