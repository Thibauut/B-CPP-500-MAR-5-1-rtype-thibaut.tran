/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** ISystem.hpp
*/

#pragma once
#include "../Entity/Entity.hpp"
#include "../Entity/EntityManager.hpp"

#include "IComponent.hpp"

namespace GameEngine {

    class ISystem {
        public:
            virtual ~ISystem() = default;

            virtual void run() = 0;

    };
}