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
                        // if (comp_hitbox->getRectangle().intersects(other_hitbox->getRectangle()) == true) {
                        //     std::cout << "collision" << std::endl;
                        // }
                    }
                }
            }

        private:
            std::shared_ptr<EntityManager> _entityManager;
            ////////////////////////////////////
            //            square              //
            ////////////////////////////////////

            ////////////////////////////////////
            //            circle              //
            ////////////////////////////////////

            ////////////////////////////////////
            //        square & circle         //
            ////////////////////////////////////

            // void circleConfig() {
            //     std::vector<std::shared_ptr<Entity>> entitiesWithHitBox;


            //     for (auto &entity : _entityManager->getEntities()) {

            //         if (entity.get()->getComponentByType<HitBoxCircle>(CONFIG::CompType::HITBOXCIRCLE) != nullptr) {
            //             entitiesWithHitBox.push_back(entity);
            //         }
            //     }

            //     for (size_t x = 0; x < entitiesWithHitBox.size(); x++) {
            //         for (size_t y = x + 1; y < entitiesWithHitBox.size(); y++) {
            //             std::shared_ptr<HitBoxCircle> circle1 = entitiesWithHitBox[x].get()->getComponentByType<HitBoxCircle>(CONFIG::CompType::HITBOXCIRCLE);
            //             std::shared_ptr<HitBoxCircle> circle2 = entitiesWithHitBox[y].get()->getComponentByType<HitBoxCircle>(CONFIG::CompType::HITBOXCIRCLE);
            //             std::shared_ptr<Position> pos1 = entitiesWithHitBox[x].get()->getComponentByType<Position>(CONFIG::CompType::POSITION);
            //             std::shared_ptr<Position> pos2 = entitiesWithHitBox[y].get()->getComponentByType<Position>(CONFIG::CompType::POSITION);

            //             if (circle1 != nullptr && circle2 != nullptr && pos1 != nullptr && pos2 != nullptr) {
            //                 float differenceX = pos2.get()->getPositionX() - pos1.get()->getPositionX();
            //                 float differenceY = pos2.get()->getPositionY() - pos1.get()->getPositionY();

            //                 float distance = std::sqrt(differenceX * differenceX + differenceY * differenceY);

            //                 if (distance < circle1.get()->getHitBoxCircleRadius() + circle2.get()->getHitBoxCircleRadius()) {
            //                     std::cout << "sysCollision : collision detected" << std::endl;
            //                 }

            //             }
            //         }
            //     }
            // }

            // void detectCircleSquareCollision() {
            //     std::vector<std::shared_ptr<Entity>> entitiesWithCircle;
            //     std::vector<std::shared_ptr<Entity>> entitiesWithSquare;

            //     for (auto &entity : _entityManager->getEntities()) {
            //         if (entity.get()->getComponentByType<HitBoxCircle>(CONFIG::CompType::HITBOXCIRCLE) != nullptr) {
            //             entitiesWithCircle.push_back(entity);
            //         } else if (entity.get()->getComponentByType<HitBoxSquare>(CONFIG::CompType::HITBOXSQUARE) != nullptr) {
            //             entitiesWithSquare.push_back(entity);
            //         }
            //     }

            //     for (auto &circleEntity : entitiesWithCircle) {
            //         for (auto &rectangleEntity : entitiesWithSquare) {
            //             std::shared_ptr<HitBoxCircle> circle = circleEntity->getComponentByType<HitBoxCircle>(CONFIG::CompType::HITBOXCIRCLE);
            //             std::shared_ptr<HitBoxSquare> rectangle = rectangleEntity->getComponentByType<HitBoxSquare>(CONFIG::CompType::HITBOXSQUARE);
            //             std::shared_ptr<Position> circlePos = circleEntity->getComponentByType<Position>(CONFIG::CompType::POSITION);
            //             std::shared_ptr<Position> rectanglePos = rectangleEntity->getComponentByType<Position>(CONFIG::CompType::POSITION);

            //             if (circle && rectangle && circlePos && rectanglePos) {
            //                 bool collisionDetected = checkCircleRectangleCollision(circle, circlePos, rectangle, rectanglePos);

            //                 if (collisionDetected) {
            //                     std::cout << "sysCollision : collision between circle & square detected" << std::endl;
            //                 }
            //             }
            //         }
            //     }
            // }


            // bool checkCircleRectangleCollision(std::shared_ptr<HitBoxCircle> circle, std::shared_ptr<Position> circlePos, std::shared_ptr<HitBoxSquare> rectangle, std::shared_ptr<Position> rectanglePos) {
            //     float circleX = circlePos->getPositionX();
            //     float circleY = circlePos->getPositionY();
            //     float circleRadius = circle->getHitBoxCircleRadius();

            //     float PosrectangleX = rectanglePos->getPositionX();
            //     float PosrectangleY = rectanglePos->getPositionY();
            //     float rectangleX = rectangle->getHitBoxSquareX();
            //     float rectangleY = rectangle->getHitBoxSquareY();

            //     float deltaX = std::abs(circleX - PosrectangleX);
            //     float deltaY = std::abs(circleY - PosrectangleY);

            //     float maxDistanceX = rectangleX / 2.0f + circleRadius;
            //     float maxDistanceY = rectangleY / 2.0f + circleRadius;

            //     if (deltaX <= maxDistanceX && deltaY <= maxDistanceY) {
            //         return true;
            //     }
            //     return false;
            // }


    };
}