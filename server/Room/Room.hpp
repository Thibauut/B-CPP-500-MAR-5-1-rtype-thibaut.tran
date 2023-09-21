/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Room.hpp
*/

#pragma once
#include <string>
#include <vector>

class Room {
    public:
        Room();
        ~Room();

    protected:
        unsigned int _id;
        std::string _name;
        unsigned int _owner;
        // std::vector<Player> _players;
};