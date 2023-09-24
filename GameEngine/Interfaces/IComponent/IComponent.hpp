/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** IComponent.hpp
*/

#pragma once

namespace GameEngine {
    class IComponent {
        public:
            virtual ~IComponent() = default;

            virtual void update() = 0;

            virtual void setComponent() = 0;
            virtual void getComponent() = 0;
            virtual const unsigned int getId() = 0;
    };
}
