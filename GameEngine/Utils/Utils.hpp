/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Utils.hpp
*/

#pragma once
#include <string>

class CLI_PlayerWeapon {
    public:
    CLI_PlayerWeapon() {}
    CLI_PlayerWeapon(std::string _degat, std::string _cadence, std::string _name, std::string _uuid) {
        degat =_degat;
        cadence =_cadence;
        name = _name;
        uuid = _uuid;
    }
    ~CLI_PlayerWeapon() {}
    std::string degat = "NULL";
    std::string cadence = "NULL";
    std::string name = "NULL";
    std::string uuid = "NULL";
};

namespace CONFIG {

    enum GameType {
        NORMAL,
        SOLOPVP,
        TEAMPVP,
        SURVIVAL,
        BR
    };
    enum WeaponType{
        Weapon1,
        Weapon2,
        Weapon3,
    };

    enum AiType {
        MOB1,
        MOB2,
        BOSS,
        ALLY,
        PLAYER,
    };

    enum CompType {
        SPRITE,
        POSITION,
        VELOCITY,
        DIRECTION,
        HEALTH,
        WEAPON,
        AI,
        HITBOXSQUARE,
        HITBOXCIRCLE,
        TIMECOMP,
        DAMAGE,
        TEAM,
        SOUND,
        WINDOW,
        DRAGGABLE,
        BUTTON_TEXT,
        EVENT,
        STRING,
        BOOL,
        RECTANGLESHAPE,
        PATH,
        CAMERA,
        MENU
    };

    enum Dir {
        UP,
        DOWN,
        RIGHT,
        LEFT,
        NONE,
    };

    enum SpriteType {
        PLAYERSPRITE,
        PLAYERSPRITEAI,
        ENEMYSPRITE,
        DEATHSPRITE,
        BULLETSPRITE,
        GUI,
        BUTTON,
        BALLSPRITE,
    };

    enum Interfaces {
        MENUDRAW,
        GAMEDRAW,
    };
}

