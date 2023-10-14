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
        SysShoot(std::list<std::shared_ptr<Entity>> &entityList) : _entities(entityList), isRunning(true) {}
        ~SysShoot() {};

        virtual void update() override {
            for (std::shared_ptr<Entity> &entityPtr : _entities) {
                if (entityPtr.get()->getType() == 4) {
                    std::shared_ptr<Position> positionComponent = entityPtr->getComponentByType<Position>(CONFIG::CompType::POSITION);
                    std::shared_ptr<Weapon> weaponComponent = entityPtr->getComponentByType<Weapon>(CONFIG::CompType::WEAPON);
                    if (positionComponent != nullptr && weaponComponent != nullptr) {
                        Timeout coulDown = weaponComponent.get()->getCoolDown();
                        int posX = positionComponent.get()->getPositionX();
                        int posY = positionComponent.get()->getPositionY();
                    }
                }
            }
        };



        private:

            bool isRunning;
            std::list<std::shared_ptr<Entity>> _entities;
    };
}