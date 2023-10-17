/*
** EPITECH PROJECT, 2023
** SysCollision
** File description:
** SysCollision
*/

#pragma once
#include "../ASystem/ASystem.hpp"
#include "../../Components/Position/Position.hpp"
#include "../../Components/HitBoxCircle/HitBoxCircle.hpp"
#include "../../Components/HitBoxSquare/HitBoxSquare.hpp"
#include "../../Utils/Utils.hpp"
#include <list>
#include <vector>
#include <cmath>

namespace GameEngine {

    class SysCollision : public ISystem {
        public:
            SysCollision(std::shared_ptr<EntityManager> entityManagerPtr) : _entityManager(entityManagerPtr) {};
            virtual ~SysCollision() = default;

            virtual void update() {
                for ( std::shared_ptr<Entity> &entity : _entityManager->getEntities()) {
                    std::shared_ptr<HitBoxSquare> comp_hitbox = entity->getComponentByType<HitBoxSquare>(CONFIG::CompType::HITBOXSQUARE);
                    std::shared_ptr<Position> comp_position = entity->getComponentByType<Position>(CONFIG::CompType::POSITION);
                    comp_hitbox->setHitboxPosition(comp_position->getPositionX(), comp_position->getPositionY());
                    for ( std::shared_ptr<Entity> &otherEntity : _entityManager->getEntities()) {
                        std::shared_ptr<HitBoxSquare> other_hitbox = otherEntity->getComponentByType<HitBoxSquare>(CONFIG::CompType::HITBOXSQUARE);
                        std::shared_ptr<Position> other_position = otherEntity->getComponentByType<Position>(CONFIG::CompType::POSITION);
                        if (entity == otherEntity) {
                            continue;
                        }
                        other_hitbox->setHitboxPosition(other_position->getPositionX(), other_position->getPositionY());
                        if (comp_hitbox->getRectangle().intersects(other_hitbox->getRectangle()) == true) {
                            std::cout << "collision" << std::endl;
                        }
                    }
                }
            }

        private:
            std::shared_ptr<EntityManager> _entityManager;
    };
}