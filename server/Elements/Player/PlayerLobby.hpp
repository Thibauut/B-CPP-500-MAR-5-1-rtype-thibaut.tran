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
#include "../../../GameEngine/Utils/Utils.hpp"


class PlayerWeapon {
    public:
    PlayerWeapon(){}
    ~PlayerWeapon(){}
    void setPlayerWeapon(double new_cadence, double new_degat, std::string new_name, std::string new_uuid)
    {
        cadence = new_cadence;
        degat = new_degat;
        name = new_name;
        uuid = new_uuid;
    }
    void setWeaponType(std::string new_type)
    {
        if (new_type == "Weapon1")
        type = CONFIG::WeaponType::Weapon1;
        if (new_type == "Weapon2")
        type = CONFIG::WeaponType::Weapon2;
        if (new_type == "Weapon3")
        type = CONFIG::WeaponType::Weapon3;
    }

    double cadence;
    double degat;
    std::string name;
    std::string uuid;
    CONFIG::WeaponType type;
};
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
        void AddPlayerWeapons(double new_cadence, double new_degat, std::string new_name, std::string new_type, std::string new_uuid) {
            PlayerWeapon weapon = PlayerWeapon();
            weapon.setPlayerWeapon(new_cadence, new_degat, new_name, new_uuid);
            weapon.setWeaponType(new_type);
            std::shared_ptr<PlayerWeapon> sharedWeapon = std::make_shared<PlayerWeapon>(weapon);
            weapons.push_back(sharedWeapon);
        }

        void setPlayerLobby(PlayerLobby &player) {
            this->username = player.username;
            this->_uuid = player._uuid;
            this->level = player.level;
            this->connection = player.connection;
            this->weapons = player.weapons;
        }

        void setPlayerEquipedWeapon(std::shared_ptr<PlayerWeapon> equipThisWeapon)
        {
            PlayerWeapon tmp = PlayerWeapon();
            tmp.cadence = equipThisWeapon->cadence;
            tmp.degat = equipThisWeapon->degat;
            tmp.name = equipThisWeapon->name;
            tmp.type = equipThisWeapon->type;
            tmp.uuid = equipThisWeapon->uuid;
            equipedWeapon1 = std::make_shared<PlayerWeapon>(tmp);
        }

        std::shared_ptr<PlayerWeapon> getEquipedWeapon(){return equipedWeapon1;}
        std::vector <std::shared_ptr<PlayerWeapon>> GetPlayerWeapons(){return weapons;}
        std::shared_ptr<PlayerWeapon> GetPlayerWeaponByUuid(std::string uuid) {
            for (auto &weapon : weapons) {
                if (weapon->uuid == uuid)
                    return weapon;
            }
            return nullptr;
        }
        void setPlayerCredit(int value)
        {
            credit = value;
        }

        void setPlayerLobbyShared(std::shared_ptr<PlayerLobby> &player) {
            this->username = player.get()->username;
            this->_uuid = player.get()->_uuid;
            this->level = player.get()->level;
            this->weapons = player.get()->weapons;
        }

        std::string getUsername() const;
        std::string getUuid() const;
        std::string getIp() const;
        int getLevel() const;
        boost::asio::ip::tcp::socket &getSocket();
        std::string username;
        std::vector <std::shared_ptr<PlayerWeapon>> weapons;
        TCPConnection::pointer connection;
    protected:
        std::string _uuid;
        std::string ip;
        int level;
        int credit;
        std::shared_ptr<PlayerWeapon> equipedWeapon1;
};

