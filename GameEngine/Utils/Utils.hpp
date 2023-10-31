/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Utils.hpp
*/

#pragma once

namespace CONFIG {

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
        CAMERA,
        WINDOW,
        DRAGGABLE,
        BUTTON,
        EVENT,
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
        ENEMYSPRITE,
        DEATHSPRITE,
        BULLETSPRITE,
        GUI,
        BUTTON,
    };
}

