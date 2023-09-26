/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** IComponent.hpp
*/

#pragma once

namespace GameEngine {

    enum ListComp {
        RENDER,
        POSITION,
        HEALTH,
        WEAPON,
        AIC,
    };

    class IComponent {
        public:
            virtual ~IComponent() = default;

            virtual GameEngine::ListComp getType() = 0;
            virtual void setType(const GameEngine::ListComp type) = 0;
            virtual int getId() = 0;
            virtual void setId(const int id) = 0;
    };
}
