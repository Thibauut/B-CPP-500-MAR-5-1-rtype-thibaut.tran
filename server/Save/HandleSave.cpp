/*
** EPITECH PROJECT, 2023
** Visual Studio Live Share (Workspace)
** File description:
** HandleSave.cpp
*/

#include "HandleSave.hpp"

using json = nlohmann::json;

HandleSave::HandleSave() {
std::ifstream input_file("../server/Save/players.json");
input_file >> players_data;
input_file.close();
}

HandleSave::~HandleSave() {

};

void HandleSave::save() {
    std::ofstream input_file("../server/Save/players.json");
    input_file << std::setw(4) << players_data << std::endl;
    input_file.close();
}

PlayerLobby HandleSave::createPlayer(std::string name, TCPConnection::pointer client)
{
    std::string uuid = boost::uuids::to_string(boost::uuids::random_generator()());
    json new_player = {
        {"uuid", uuid},
        {"name", name},
        {"level", 1},
        {"online", true}
    };
    players_data["players"].push_back(new_player);
    std::ofstream output_file("../server/Save/players.json");
    output_file << players_data;
    output_file.close();
    PlayerLobby pl = PlayerLobby(name, uuid, 1, client);
    return pl;
}
void HandleSave::removePlayer(boost::uuids::uuid uuid) {}

void HandleSave::updatePlayer(PlayerLobby pl) {
    for (auto &player : players_data["players"]) {
        if (player["uuid"] == pl.getUuid()) {
            player["level"] = pl.getLevel();
            break;
        }
    }
    save();
}

void HandleSave::setPlayerStatus(bool status, std::string uuid) {
    for (auto &player : players_data["players"]) {
        if (player["uuid"] == uuid) {
            player["online"] = status;
            break;
        }
    }
    save();
}

std::shared_ptr<PlayerLobby> HandleSave::findPlayerByName(std::string name) {
    for (auto &player : players_data["players"]) {
        if (player["name"] == name) {
            std::string name = player["name"];
            std::string uuid = player["uuid"];
            int level = player["level"];
            PlayerLobby pl_tmp = PlayerLobby(name, uuid, level);
            std::shared_ptr<PlayerLobby> pl = std::make_shared<PlayerLobby>(pl_tmp);
            return pl;
        }
    }
    return nullptr;
}

std::shared_ptr<PlayerLobby> HandleSave::findPlayerByUuid(std::string uuid) {
    for (auto &player : players_data["players"]) {
        if (player["uuid"] == uuid) {
            std::string name = player["name"];
            std::string uuid = player["uuid"];
            int level = player["level"];
            PlayerLobby pl_tmp = PlayerLobby(name, uuid, level);
            std::shared_ptr<PlayerLobby> pl = std::make_shared<PlayerLobby>(pl_tmp);
            return pl;
        }
    }
    return nullptr;
}

bool HandleSave::PlayerExist(std::string name) {
    for (auto &player : players_data["players"]) {
        if (player["name"] == name)
            return true;
    }
    return false;
};