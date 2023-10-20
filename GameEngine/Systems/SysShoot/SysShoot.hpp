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
#include "../../Components/Cooldown/Cooldown.hpp"
#include "../../Components/Direction/Direction.hpp"
#include "../../Utils/Timeout.hpp"
#include <cmath>
#include <chrono>
#include <random>

namespace GameEngine {

    class SysShoot : public ISystem {
        public:
        SysShoot(std::shared_ptr<EntityManager> entityList) : _manager(entityList), isRunning(true){}
        ~SysShoot() {};

        virtual void update() override {
            for (std::shared_ptr<Entity> &entityPtr : _manager->getEntities()) {
                if (entityPtr->getType() == 4) {
                    auto diretion = entityPtr->getComponentByType<Direction>(CONFIG::CompType::DIRECTION);
                    double distance = 1.5;
                    double orientation_radians = diretion->getOriantation() * (M_PI / 180.0);
                    double delta_x = distance * cos(orientation_radians);
                    double delta_y = distance * sin(orientation_radians);

                    std::shared_ptr<Position> positionComponent = entityPtr->getComponentByType<Position>(CONFIG::CompType::POSITION);
                    std::shared_ptr<Cooldown> couldownComponent = entityPtr->getComponentByType<Cooldown>(CONFIG::CompType::TIMECOMP);
                    if (couldownComponent.get()->isFinish("bullet")) {
                        if (positionComponent != nullptr) {
                            positionComponent.get()->setPosition(positionComponent.get()->getPositionX() + delta_x, positionComponent.get()->getPositionY() + delta_y);
                        }
                        couldownComponent.get()->reset("bullet");
                    }
                }
            }
        };



        private:
            bool isRunning;
            std::shared_ptr<EntityManager> _manager;
    };
}