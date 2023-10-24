/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** ISystem.hpp
*/

#pragma once

namespace GameEngine {

    class ISystem {
        public:
            virtual ~ISystem() = default;
            virtual void update() = 0;
            // virtual bool isActive() = 0;
            // virtual void run() = 0;
            // virtual void stop() = 0;
    };
}