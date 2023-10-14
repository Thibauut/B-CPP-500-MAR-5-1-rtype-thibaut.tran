/*
** EPITECH PROJECT, 2023
** SANJII & ZORO
** File description:
** SysShoot.hpp
*/

#pragma once
#include "../ASystem/ASystem.hpp"
#include "../../Components/Position/Position.hpp"
#include "../../Components/Weapon/Weapon.hpp"
#include "../../Components/Sprite/Sprite.hpp"
#include "../../Utils/Timeout.hpp"
#include <chrono>
#include <random>

namespace GameEngine {

    class SysShoot : public ISystem {
        SysShoot(std::shared_ptr<EntityManager> entityList) : _manager(entityList), isRunning(true) {}
        ~SysShoot() {};

        virtual void update() override {
            for (std::shared_ptr<Entity> &entityPtr : _manager->getEntities()) {
                if (entityPtr->getType() == 4) {
                    std::shared_ptr<Position> positionComponent = entityPtr->getComponentByType<Position>(CONFIG::CompType::POSITION);
                    std::shared_ptr<Weapon> weaponComponent = entityPtr->getComponentByType<Weapon>(CONFIG::CompType::WEAPON);
                    if (positionComponent != nullptr && weaponComponent != nullptr) {
                        Timeout coulDown = weaponComponent->getCoolDown();
                        int posX = positionComponent->getPositionX();
                        int posY = positionComponent->getPositionY();
                    }
                }
            }
        };



        private:

            bool isRunning;
            std::shared_ptr<EntityManager> _manager;
    };
}