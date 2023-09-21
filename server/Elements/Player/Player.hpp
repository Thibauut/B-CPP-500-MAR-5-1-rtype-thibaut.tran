/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Player.hpp
*/

#pragma once
#include "PlayerLobby.hpp"
#include <string>

class Player {
    public:
        Player(PlayerLobby player);
        ~Player();


    protected:
        std::string username;
};