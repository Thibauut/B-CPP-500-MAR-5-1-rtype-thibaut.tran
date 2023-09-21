/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Render.hpp
*/

#pragma once
#include "AComponent.hpp"

namespace GameEngine {

    class Render : public GameEngine::AComponenent {
        public:
            Render() {};
            ~Render() = default;
            
            void setComponent() {
                std::cout << "Component : {render.set}" << std::endl;
            };

        private:
            std::string _pathTexture;
            int _width;
            int _height;
    };
}