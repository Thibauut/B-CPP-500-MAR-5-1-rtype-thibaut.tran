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
        PlayerLobby(const std::string username);
        ~PlayerLobby();

        std::string getUsername() const;
        std::string getUid() const;
        std::string getIp() const;

        std::string username;
    protected:
        std::string _uid;
        std::string ip;
};

// class Player {
//     public:
//         Player(PlayerLobby player);
//         ~Player();


//     protected:
//         std::string username;
// };