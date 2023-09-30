/*
** EPITECH PROJECT, 2023
** SysCollision
** File description:
** SysCollision
*/

#pragma once
#include "../ASystem/ASystem.hpp"
#include "../../Utils/Utils.hpp"

namespace GameEngine {

    class SysCollision : public ISystem {
        public:
            SysCollision(std::shared_ptr<EntityManager> entityManagerPtr) : _entityManager(entityManagerPtr) {};
            virtual ~SysCollision() = default;

            virtual void update() {
                // Logique de détection de collision/HITBOX (à implémenter)
            }
        private:
            std::shared_ptr<EntityManager> _entityManager;
    };
}