/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Server.cpp
*/

#include "Server.hpp"

Server::Server(boost::asio::io_context& io_context, int port) : _menu(io_context), _port(port) { initServer();}

Server::~Server() {}

void Server::initServer() {}

void Server::run(boost::asio::io_context &context)
{
     try {
        std::thread refresh_thread(&Server::refresh, this);
        context.run();
        refresh_thread.join();
    } catch (std::exception &e) {}
}

bool Server::isExistPlayer(std::string uuid) {
    for (PlayerLobby player : _players) {
        if (player.getUuid() == uuid)
            return true;
    }
    return false;
}

void Server::refreshFromDb() {
    nlohmann::json players_data;
    std::ifstream input_file("Save/players.json");
    input_file >> players_data;
    input_file.close();
    for (json &player : players_data["players"]) {
        if (player["online"] == false && isExistPlayer(player["uuid"]) == true) {
            _players.erase(std::remove_if(_players.begin(), _players.end(), [player](PlayerLobby p) { return p.getUuid() == player["uuid"]; }), _players.end());
        }
        if (player["online"] == true && isExistPlayer(player["uuid"]) == false) {
            _players.push_back(PlayerLobby(player["name"], player["uuid"], player["level"]));
        }
    }
}

void Server::refresh()
{
    // PlayerLobby player = PlayerLobby("Tbz");
    // RoomLobby lobby = RoomLobby(player, 4, "le galion");
    // lobby.startGame();
    while (1) {
        refreshFromDb();
        _menu.getAllTcpRequest(_save, _lobbys);
    }
}

void Server::createRoom(PlayerLobby owner, std::string name, int _nbSlots)
{
    // _lobbys.push_back(RoomLobby(owner, _nbSlots, name));
}

void Server::addClientToRoom(int pos, PlayerLobby client)
{
    // _lobby.at(pos).addPlayer(client);
}

void Server::deleteRoom(int pos)
{
    // _lobbys.erase(_lobbys.begin() + pos);
}