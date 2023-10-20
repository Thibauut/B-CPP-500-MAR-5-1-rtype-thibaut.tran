/*
** EPITECH PROJECT, 2023
** SANJII & ZORO
** File description:
** SysShoot.hpp
*/

#pragma once
#include "../ASystem/ASystem.hpp"
#include "../../Utils/Timeout.hpp"
#include <chrono>
#include <random>

namespace GameEngine {

    class SysClear : public ISystem {
        public:
        SysClear(std::shared_ptr<EntityManager> entityList) : _manager(entityList), isRunning(true){}
        ~SysClear() {};

        virtual void update() override {
            for (std::shared_ptr<Entity> &entity : _manager->getEntities()) {
                if (entity->DestroyStarted() == false && entity->getIsDeath() == true)
                    entity.get()->startDestroy();
            }
            for (std::shared_ptr<Entity> &entity : _manager->getEntities()) {
                if (entity.get()->canDestroy() && entity->DestroyStarted() == true) {
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