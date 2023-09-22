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
        Room(std::string name, std::string owner_uid, unsigned int nbSlots);
        ~Room();

    protected:
        std::string _uid;
        std::string _name;
        std::string _owner_uid;
        unsigned int _nbPlayers;
        unsigned int _nbSlots;
        // std::vector<Player> _players;
};