/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** PlayerLobby.cpp
*/

#include "PlayerLobby.hpp"

PlayerLobby::PlayerLobby(const std::string &username) : username(username)
{
}

PlayerLobby::~PlayerLobby()
{
}

std::string PlayerLobby::getUsername() const
{
    return username;
}

std::string PlayerLobby::getUid() const
{
    return _uid;
}

std::string PlayerLobby::getIp() const
{
    return ip;
}