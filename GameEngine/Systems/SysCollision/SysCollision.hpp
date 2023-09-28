/*
** EPITECH PROJECT, 2023
** SysCollision
** File description:
** SysCollision
*/

#pragma once
#include "ASystem.hpp"

namespace GameEngine {

    class SysCollision : public ISystem {
        public:
            SysCollision() {};
            ~SysCollision() {};

            virtual void run() override {
                // Logique de détection de collision/HITBOX (à implémenter)
            }
        private:
    };

}