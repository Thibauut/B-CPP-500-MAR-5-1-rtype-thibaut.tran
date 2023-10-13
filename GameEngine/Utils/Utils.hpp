/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Utils.hpp
*/

#pragma once

namespace CONFIG {

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
    };

    enum Dir {
        UP,
        DOWN,
        RIGHT,
        LEFT,
        NONE,
    };
}

