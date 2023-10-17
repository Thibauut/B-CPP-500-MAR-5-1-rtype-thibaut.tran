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
#include "../../Components/Damage/Damage.hpp"
#include "../../Components/Health/Health.hpp"
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
                            HandleDamage(entity, otherEntity);
                            return;
                        }
                    }
                }
            }
            void  HandleDamage(std::shared_ptr<Entity> &entity1, std::shared_ptr<Entity> &entity2) {
                // std::cout <<"collision with " << entity1->getType()<< " and " << entity2->getType() << std::endl;
                if (entity2.get()->getType() == 4) {
                    std::shared_ptr<Damage> damage = entity2->getComponentByType<Damage>(CONFIG::CompType::DAMAGE);
                    if (entity1->getType() == 1 || entity1->getType() == 2) {
                        std::shared_ptr<Health> health = entity1->getComponentByType<Health>(CONFIG::CompType::HEALTH);
                        health->setHealth(health->getHealth() - 1);
                        // std::cout << "mob life: "<< health->getHealth() << std::endl;
                        if (health->getHealth() <= 0) {
                            std::cout << "is dead" << std::endl;
                            _entityManager->deleteEntity(entity1->getId());
                            return;
                        }
                        _entityManager->deleteEntity(entity2->getId());
                    }
                }
                if (entity1.get()->getType() == 4) {
                    std::shared_ptr<Damage> damage = entity1->getComponentByType<Damage>(CONFIG::CompType::DAMAGE);
                    if (entity2->getType() == 1 || entity2->getType() == 2) {
                        std::shared_ptr<Health> health = entity2->getComponentByType<Health>(CONFIG::CompType::HEALTH);
                        health->setHealth(health->getHealth() - 1);
                        if (health->getHealth() <= 0) {
                            std::cout << "is dead" << std::endl;
                            _entityManager->deleteEntity(entity2->getId());
                            return;
                        }
                        _entityManager->deleteEntity(entity1->getId());
                    }
                }
            }
        private:
            std::shared_ptr<EntityManager> _entityManager;
    };
}