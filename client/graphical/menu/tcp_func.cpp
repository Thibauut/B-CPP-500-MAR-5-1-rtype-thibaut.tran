/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** connexion.cpp
*/

#include "../../include/menu.hpp"

void Menu::UpdateRoom() {
    _roomList.clear();
    _tcpConnection->GetRoomList();
    if (!_tcpConnection->rooms.empty()) {
        for (auto &roomtcp : _tcpConnection->rooms) {
            Room *room = new Room();
            sfmlFunc.CreateButton(room->room, room->roomText, _font, roomtcp->name, sf::Vector2f(1000, 40), sf::Vector2f(400, 460 + (_roomSizeIndex * _roomList.size())), 150);
            room->nbPlayers.setFont(_font);
            room->nbPlayers.setString(roomtcp->slot);
            room->nbPlayers.setCharacterSize(24);
            room->nbPlayers.setFillColor(sf::Color::White);
            room->nbPlayers.setPosition(sf::Vector2f(400, 460 + (_roomSizeIndex * _roomList.size())) + sf::Vector2f(40, 10));
            room->roomuuid = roomtcp->uuid;
            std::cout << room->roomuuid << std::endl;
            _roomList.push_back(room);
        }
    }
}

void Menu::UpdatePlayerList() {
    _playerList.clear();
    _tcpConnection->GetRoomInfo(_selectedRoom->roomuuid);
    if (!_tcpConnection->players.empty()) {
        for (auto &playertcp : _tcpConnection->players) {
            Player *player = new Player();
            sfmlFunc.CreateButton(player->room, player->playerName, _font, playertcp->name, sf::Vector2f(1000, 40), sf::Vector2f(400, 460 + (_roomSizeIndex * _playerList.size())), 150);
            player->playerLevel.setFont(_font);
            player->playerLevel.setString(playertcp->level);
            player->playerLevel.setCharacterSize(24);
            player->playerLevel.setFillColor(sf::Color::White);
            player->playerLevel.setPosition(sf::Vector2f(400, 460 + (_roomSizeIndex * _playerList.size())) + sf::Vector2f(40, 10));
            _playerList.push_back(player);
        }
    }
}
