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
#include "../../Components/TimeComp/TimeComp.hpp"
#include "../../Components/Direction/Direction.hpp"
#include "../../Utils/Timeout.hpp"
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
                    std::shared_ptr<Position> positionComponent = entityPtr->getComponentByType<Position>(CONFIG::CompType::POSITION);
                    std::shared_ptr<TimeComp> couldownComponent = entityPtr->getComponentByType<TimeComp>(CONFIG::CompType::TIMECOMP);
                    int distance = entityPtr->getComponentByType<Direction>(CONFIG::CompType::DIRECTION)->getDirection();
                    if (couldownComponent.get()->couldown_is_finish()) {
                        if (positionComponent != nullptr) {
                            positionComponent.get()->setPosition(positionComponent.get()->getPositionX() + distance, positionComponent.get()->getPositionY());
                        }
                        couldownComponent.get()->reset_couldown();
                    }
                }
            }
        };



        private:
            bool isRunning;
            std::shared_ptr<EntityManager> _manager;
    };
}