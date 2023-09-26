/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** ISystem.hpp
*/

#pragma once

#include "../../Entity/EntityManager/EntityManager.hpp"

namespace GameEngine {

    class ISystem {
        public:
            virtual ~ISystem() = default;

            virtual void update() = 0;

    };
}