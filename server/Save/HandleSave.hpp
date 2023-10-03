/*
** EPITECH PROJECT, 2023
** Visual Studio Live Share (Workspace)
** File description:
** HandleSave.hpp
*/

#pragma once

#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include <boost/uuid/uuid_generators.hpp>
// #include <boost/uuid/uuid.hpp>
#include "../Elements/Player/PlayerLobby.hpp"
#include <boost/uuid/uuid_io.hpp>

using json = nlohmann::json;

class HandleSave {
    public:
    HandleSave();
    ~HandleSave();

    void save();

    // PLAYER
    PlayerLobby createPlayer(std::string name, TCPConnection::pointer client);
    void removePlayer(boost::uuids::uuid uuid);
    void updatePlayer(PlayerLobby player);
    void setPlayerStatus(bool status, std::string uuid);
    std::shared_ptr<PlayerLobby> findPlayerByName(std::string name);
    std::shared_ptr<PlayerLobby> findPlayerByUuid(std::string uuid);
    bool PlayerExist(std::string name);

    // HIGH_SCORE
    // LOBBY

    json players_data;
};