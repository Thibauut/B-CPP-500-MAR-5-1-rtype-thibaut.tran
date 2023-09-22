/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Player.hpp
*/

#pragma once
#include <string>

class PlayerLobby {
    public:
        PlayerLobby(const std::string username, std::string uuid, int level);
        PlayerLobby() {};
        ~PlayerLobby();

        std::string getUsername() const;
        std::string getUuid() const;
        std::string getIp() const;
        int getLevel() const;

        std::string username;

    protected:
        std::string _uuid;
        std::string ip;
        int level;
};