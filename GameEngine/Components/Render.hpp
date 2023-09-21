/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Render.hpp
*/

#pragma once
#include "../AComponent.hpp"

namespace GameEngine {
    class Render : public GameEngine::AComponenent {
        public:
            Render();
            virtual ~Render() = default;
            
            void update() {
                std::cout << "Component : {rendered}" << std::endl;
            };

            void setComponent() {};
            void getComponent() {};
    };
}