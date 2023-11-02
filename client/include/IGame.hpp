/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** IGame.hpp
*/
#pragma once

#include "../network/OpenUDP/OpenUDP.hpp"
#include "../../GameEngine/GameEngine.hpp"


class IGame {
    public:
        virtual ~IGame() = default;
        virtual void InitBackground() = 0;
        virtual void AnimateBackground() = 0;
        virtual void Loop() = 0;
        virtual void HandleEvents() = 0;
        virtual void Draw() = 0;
};

