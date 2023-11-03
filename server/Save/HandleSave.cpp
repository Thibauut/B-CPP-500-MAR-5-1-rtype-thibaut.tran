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
        {"online", true},
        {"credit", 1000},
        {"weapons", json::array()}
    };
    json gun = {
        {"name", "weapon1"},
        {"degat", 15},
        {"cadence", 2},
        {"type", "Weapon1"},
        {"uuid", boost::uuids::to_string(boost::uuids::random_generator()())}
    };
    new_player["weapons"].push_back(gun);
    players_data["players"].push_back(new_player);
    std::ofstream output_file("../server/Save/players.json");
    output_file << players_data;
    output_file.close();
    PlayerLobby pl = PlayerLobby(name, uuid, 1, client);
    pl.AddPlayerWeapons(gun["cadence"], gun["degat"],gun["name"],gun["type"],gun["uuid"]);
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
            int credit = player["credit"];
            PlayerLobby pl_tmp = PlayerLobby(name, uuid, level);
            for (auto &playerWeapon : player["weapons"]) {
                std::string name = playerWeapon["name"];
                double cadence = playerWeapon["cadence"];
                double degat = playerWeapon["degat"];
                std::string uuid = playerWeapon["uuid"];
                std::string type = playerWeapon["type"];
                pl_tmp.AddPlayerWeapons(cadence, degat, name, type, uuid);
            }
            std::shared_ptr<PlayerLobby> pl = std::make_shared<PlayerLobby>(pl_tmp);
            pl->setPlayerCredit(credit);
            for (auto &weap : pl_tmp.weapons) {
                if (weap->type == CONFIG::WeaponType::Weapon1)
                    pl->AddPlayerWeapons(weap->cadence, weap->degat, weap->name, "Weapon1", weap->uuid);
                if (weap->type == CONFIG::WeaponType::Weapon2)
                    pl->AddPlayerWeapons(weap->cadence, weap->degat, weap->name, "Weapon2", weap->uuid);
                if (weap->type == CONFIG::WeaponType::Weapon3)
                    pl->AddPlayerWeapons(weap->cadence, weap->degat, weap->name, "Weapon3", weap->uuid);
            }
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
            int credit = player["credit"];
            PlayerLobby pl_tmp = PlayerLobby(name, uuid, level);
            for (auto &playerWeapon : player["weapons"]) {
                std::string name = playerWeapon["name"];
                double cadence = playerWeapon["cadence"];
                double degat = playerWeapon["degat"];
                std::string uuid = playerWeapon["uuid"];
                std::string type = playerWeapon["type"];
                pl_tmp.AddPlayerWeapons(cadence, degat, name, type, uuid);
            }
            std::shared_ptr<PlayerLobby> pl = std::make_shared<PlayerLobby>(pl_tmp);
            pl->setPlayerCredit(credit);
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