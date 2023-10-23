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
#include "../../Components/Team/Team.hpp"
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
                    if (comp_hitbox == nullptr || comp_position == nullptr) {
                        continue;
                    }
                    comp_hitbox->setHitboxPosition(comp_position->getPositionX(), comp_position->getPositionY());
                    for ( std::shared_ptr<Entity> &otherEntity : _entityManager->getEntities()) {
                        std::shared_ptr<HitBoxSquare> other_hitbox = otherEntity->getComponentByType<HitBoxSquare>(CONFIG::CompType::HITBOXSQUARE);
                        std::shared_ptr<Position> other_position = otherEntity->getComponentByType<Position>(CONFIG::CompType::POSITION);
                        if (other_hitbox == nullptr || other_position == nullptr) {
                            continue;
                        }
                        if (entity == otherEntity) {
                            continue;
                        }
                        other_hitbox->setHitboxPosition(other_position->getPositionX(), other_position->getPositionY());
                        if (comp_hitbox->getRectangle().intersects(other_hitbox->getRectangle()) == true) {
                            HandleDamage(entity, otherEntity);
                        }
                    }
                }
            }
            void  HandleDamage(std::shared_ptr<Entity> &entity1, std::shared_ptr<Entity> &entity2) {
                if (entity2.get()->getType() == 4) {
                    std::shared_ptr<Damage> damage = entity2->getComponentByType<Damage>(CONFIG::CompType::DAMAGE);
                    if (entity1->getType() == 2 || entity1->getType() == 1) {
                        if (entity1->getComponentByType<Team>(CONFIG::CompType::TEAM)->getTeam() != entity2->getComponentByType<Team>(CONFIG::CompType::TEAM)->getTeam()) {
                            std::shared_ptr<Health> health = entity1->getComponentByType<Health>(CONFIG::CompType::HEALTH);
                            if (entity2->getIsDeath() != true)
                                health->setHealth(health->getHealth() - damage->getDamage());
                            if (health->getHealth() <= 0) {
                                entity1->setIsDeath(true);
                                return;
                            }
                            entity2->setIsDeath(true);
                        }
                    }
                }
                // if (entity1.get()->getType() == 4) {
                //     std::shared_ptr<Damage> damage = entity1->getComponentByType<Damage>(CONFIG::CompType::DAMAGE);
                //     if (entity2->getType() == 2 && entity1->getComponentByType<Team>(CONFIG::CompType::TEAM)->getTeam() != entity1->getComponentByType<Team>(CONFIG::CompType::TEAM)->getTeam()) {
                //         std::shared_ptr<Health> health = entity2->getComponentByType<Health>(CONFIG::CompType::HEALTH);
                //         if (entity1->getIsDeath() != true)
                //             health->setHealth(health->getHealth() - damage->getDamage());
                //         if (health->getHealth() <= 0) {
                //             entity2->setIsDeath(true);
                //             return;
                //         }
                //         entity1->setIsDeath(true);
                //     }
                // }
            }
        private:
            std::shared_ptr<EntityManager> _entityManager;
    };
}