/*
** EPITECH PROJECT, 2023
** SANJII & ZORO
** File description:
** SysShoot.hpp
*/

#pragma once
#include "../ASystem/ASystem.hpp"
#include "../../Components/Sprite/Sprite.hpp"
#include "../../Utils/Timeout.hpp"
#include <chrono>
#include <random>

namespace GameEngine {

    class SysClearClient : public ISystem {
        public:
        SysClearClient(std::shared_ptr<EntityManager> entityList) : _manager(entityList), isRunning(true){}
        ~SysClearClient() {};

        virtual void update() override {
            for (std::shared_ptr<Entity>&entity : _manager->getEntities()) {
                if (entity->getIsDeath() == true && entity->getType() != 2) {
                    _manager->deleteEntity(entity->getUuid());
                    break;
                }
            }
        };

        private:
            bool isRunning;
            std::shared_ptr<EntityManager> _manager;
    };
}
