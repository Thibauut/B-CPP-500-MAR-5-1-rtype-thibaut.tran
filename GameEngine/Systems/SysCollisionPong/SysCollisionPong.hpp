/*
** EPITECH PROJECT, 2023
** SysCollision
** File description:
** SysCollision
*/

#pragma once
#include "../ASystem/ASystem.hpp"
#include "../../Components/Position/Position.hpp"
#include "../../Components/Sprite/Sprite.hpp"
#include "../../Components/HitBoxSquare/HitBoxSquare.hpp"
#include "../../Components/Direction/Direction.hpp"
#include "../../Utils/Utils.hpp"
#include "../../Utils/Timeout.hpp"
#include <list>
#include <vector>
#include <cmath>

namespace GameEngine {

    class SysCollisionPong : public ISystem {
        public:
            SysCollisionPong(std::shared_ptr<EntityManager> entityManagerPtr) : _entityManager(entityManagerPtr) {};
            virtual ~SysCollisionPong() = default;

            virtual void update() {
                for (std::shared_ptr<Entity> &entity : _entityManager->getEntities()) {
                    if (entity->getType() != 3 && entity->getType() != 6) {
                        std::shared_ptr<Position> comp_positionPlayer = entity->getComponentByType<Position>(CONFIG::CompType::POSITION);
                        std::shared_ptr<Position> comp_positionBall = _entityManager.get()->getEntityByType(3)->getComponentByType<Position>(CONFIG::CompType::POSITION);

                        std::shared_ptr<HitBoxSquare> comp_hitboxPlayer = entity->getComponentByType<HitBoxSquare>(CONFIG::CompType::HITBOXSQUARE);
                        comp_hitboxPlayer->setHitboxPosition(comp_positionPlayer->getPositionX(), comp_positionPlayer->getPositionY());
                        comp_hitboxPlayer->setHitboxSize(70, 250);

                        std::shared_ptr<HitBoxSquare> comp_hitboxBall = _entityManager.get()->getEntityByType(3)->getComponentByType<HitBoxSquare>(CONFIG::CompType::HITBOXSQUARE);
                        comp_hitboxBall->setHitboxPosition(comp_positionBall->getPositionX(), comp_positionBall->getPositionY());
                        comp_hitboxBall->setHitboxSize(60, 60);

                        if(comp_hitboxPlayer->getRectangle().intersects(comp_hitboxBall->getRectangle()) == true) {
                            std::shared_ptr<Direction> direction = _entityManager.get()->getEntityByType(3)->getComponentByType<Direction>(CONFIG::CompType::DIRECTION);
                            direction->setDirectionX(direction->getDirectionX() * -1);
                            return;
                        }
                    }
                }
            }
        private:
            std::shared_ptr<EntityManager> _entityManager;
            bool shouldBreak = false;
    };
}