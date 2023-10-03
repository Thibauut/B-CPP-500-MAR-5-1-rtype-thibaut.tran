/*
** EPITECH PROJECT, 2023
** SysMovement
** File description:
** SysMovement
*/

#pragma once
#include "../ASystem/ASystem.hpp"
#include "../../Utils/Utils.hpp"
#include <list>

namespace GameEngine {

    class SysMovement : public ISystem {
        public:
            SysMovement(std::shared_ptr<EntityManager> entityManagerPtr) : _entityManager(entityManagerPtr) {};
            virtual ~SysMovement() = default;

            virtual void update() {
                for (auto& entity : _entityManager->getEntities()) {
                    std::shared_ptr<Position> pos;
                    std::shared_ptr<Direction> dir;
                    std::shared_ptr<Velocity> vel;

                    if (entity.get()->getComponentByType<Position>(CONFIG::CompType::POSITION) != nullptr) {
                        pos = entity.get()->getComponentByType<Position>(CONFIG::CompType::POSITION);
                    }
                    if (entity.get()->getComponentByType<Direction>(CONFIG::CompType::DIRECTION) != nullptr) {
                        dir = entity.get()->getComponentByType<Direction>(CONFIG::CompType::DIRECTION);
                    }
                    if (entity.get()->getComponentByType<Velocity>(CONFIG::CompType::VELOCITY) != nullptr) {
                        vel = entity.get()->getComponentByType<Velocity>(CONFIG::CompType::VELOCITY);
                    }
                    
                    if (pos != nullptr && dir != nullptr && vel != nullptr) {
                        CONFIG::Dir actualDir = dir.get()->getDirection();
                        switch (actualDir) {
                            case CONFIG::Dir::RIGHT:
                                std::cout << "Sys Mov : right detected" << std::endl;
                                pos.get()->setPositionX(pos.get()->getPositionX() + (1 * vel.get()->getVelocity()));
                                break;
                            case CONFIG::Dir::LEFT:
                                std::cout << "Sys Mov : left detected" << std::endl;
                                pos.get()->setPositionX(pos.get()->getPositionX() - (1 * vel.get()->getVelocity()));
                                break;
                            case CONFIG::Dir::UP:
                                std::cout << "Sys mov : up detected" << std::endl;
                                pos.get()->setPositionY(pos.get()->getPositionY() - (1 * vel.get()->getVelocity()));
                                break;
                            case CONFIG::Dir::DOWN:
                                std::cout << "Sys mov : down detected" << std::endl;
                                pos.get()->setPositionY(pos.get()->getPositionY() + (1 * vel.get()->getVelocity()));
                                break;
                            case CONFIG::Dir::NONE:
                                std::cout << "Sys mov : none detected" << std::endl;
                                pos.get()->setPosition(pos.get()->getPositionX(), pos.get()->getPositionY());
                            default:
                                break;
                        };
                    }
                }
            }
        private:
            std::shared_ptr<EntityManager>  _entityManager;
    };
}
