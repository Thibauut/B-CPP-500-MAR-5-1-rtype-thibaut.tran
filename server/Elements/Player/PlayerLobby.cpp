/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** PlayerLobby.cpp
*/

#include "PlayerLobby.hpp"

PlayerLobby::PlayerLobby(const std::string username, std::string uuid, int level, TCPConnection::pointer client) : username(username), _uuid(uuid), level(level), connection(client)
{}

PlayerLobby::PlayerLobby(const std::string username, std::string uuid, int level) : username(username), _uuid(uuid), level(level)
{}

PlayerLobby::PlayerLobby(TCPConnection::pointer client) : connection(client)
{}

PlayerLobby::~PlayerLobby() {}

std::string PlayerLobby::getUsername() const
{
    return username;
}

std::string PlayerLobby::getUuid() const
{
    return _uuid;
}

std::string PlayerLobby::getIp() const
{
    return ip;
}

int PlayerLobby::getLevel() const
{
    return level;
}

boost::asio::ip::tcp::socket &PlayerLobby::getSocket()
{
    return connection->socket();
}