/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Player.hpp
*/

#pragma once
#include <string>
#include <memory>
#include "../../Socket/TCP/TCPConnexion.hpp"

class PlayerLobby {
    public:
        PlayerLobby(const std::string username, std::string uuid, int level, TCPConnection::pointer client);
        PlayerLobby(const std::string username, std::string uuid, int level);
        PlayerLobby(TCPConnection::pointer client);
        PlayerLobby(PlayerLobby &copy) {
            this->username = copy.username;
            this->_uuid = copy._uuid;
            this->level = copy.level;
        }
        ~PlayerLobby();

        void setPlayerLobby(PlayerLobby &player) {
            this->username = player.username;
            this->_uuid = player._uuid;
            this->level = player.level;
            this->connection = player.connection;
        }

        void setPlayerLobbyShared(std::shared_ptr<PlayerLobby> &player) {
            this->username = player.get()->username;
            this->_uuid = player.get()->_uuid;
            this->level = player.get()->level;
        }

        std::string getUsername() const;
        std::string getUuid() const;
        std::string getIp() const;
        int getLevel() const;
        boost::asio::ip::tcp::socket &getSocket();

        std::string username;

        TCPConnection::pointer connection;
    protected:
        std::string _uuid;
        std::string ip;
        int level;
};

