/*
** EPITECH PROJECT, 2023
** SysCollision
** File description:
** SysCollision
*/

#pragma once
#include "../ASystem/ASystem.hpp"
#include "../../Components/Position/Position.hpp"
#include "../../Components/Score/Score.hpp"
#include "../../Components/Direction/Direction.hpp"
#include "../../Utils/Utils.hpp"
#include "../../Utils/Timeout.hpp"
#include <list>
#include <vector>
#include <cmath>

namespace GameEngine {

    class SysMoveBallPong : public ISystem {
        public:
            SysMoveBallPong(std::shared_ptr<EntityManager> entityManagerPtr) : _entityManager(entityManagerPtr) {
                _timeMove = Timeout(0.0009);
            };
            virtual ~SysMoveBallPong() = default;

            virtual void update() {
                for (std::shared_ptr<Entity> &entityPtr : _entityManager->getEntities()) {
                    if (entityPtr->getType() == 3) {
                        std::shared_ptr<Position> positionComponent = entityPtr->getComponentByType<Position>(CONFIG::CompType::POSITION);
                        std::shared_ptr<Direction> directionComponent = entityPtr->getComponentByType<Direction>(CONFIG::CompType::DIRECTION);
                        if (positionComponent != nullptr&& directionComponent != nullptr && _timeMove.can_execute()) {
                            std::pair<int, int> posBall = positionComponent->getPosition();

                            //if the ball hit top & bottom
                            if (posBall.second < 0|| posBall.second > 1080 - 60) {
                                directionComponent->setDirectionY(directionComponent->getDirectionY() * -1);
                            }

                            //if the ball goes left & right means the player x scorect
                            if (posBall.first < 0 - 60) {
                                resetPosBall(posBall, positionComponent, directionComponent);
                                for (std::shared_ptr<Entity> &entityPtr : _entityManager->getEntities()) {
                                    if (entityPtr->getType() == 2) {
                                        std::shared_ptr<Score> score = entityPtr->getComponentByType<Score>(CONFIG::CompType::SCORE);
                                        if (score) {
                                            int score2 = score->getScore();
                                            score2 += 1;
                                            score->setScore(score2);
                                            break;
                                        }
                                    }
                                }
                            }
                            if (posBall.first > 1920 + 60) {
                                resetPosBall(posBall, positionComponent, directionComponent);
                                for (std::shared_ptr<Entity> &entityPtr : _entityManager->getEntities()) {
                                    if (entityPtr->getType() == 6) {
                                        std::shared_ptr<Score> score = entityPtr->getComponentByType<Score>(CONFIG::CompType::SCORE);
                                        if (score) {
                                            int score1 = score->getScore();
                                            score1 += 1;
                                            score->setScore(score1);
                                            break;
                                        }
                                    }
                                }
                            }
                            //set positions
                            posBall.first += speed * directionComponent->getDirectionX();
                            posBall.second += speed * directionComponent->getDirectionY();
                            positionComponent.get()->setPosition(posBall.first, posBall.second);
                            _timeMove.Start();
                        }
                    }
                }
            }
            void  resetPosBall(std::pair<int, int> &posBall, std::shared_ptr<Position> &positionComponent, std::shared_ptr<Direction> &directionComponent) {
                srand(time(NULL));
                posBall.first = (1920/2 - 60/2);
                posBall.second = (1080/2 - 60/2);
                positionComponent.get()->setPosition(posBall.first, posBall.second);

               directionComponent->setDirectionX(1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 - 1))));
                if (rand() % 2 == 0) {
                    directionComponent->setDirectionX(-1);
                }
	            directionComponent->setDirectionY(1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 - 1))));
                if (rand() % 2 == 0) {
                    directionComponent->setDirectionY(-1);
                }
            }

        private:
            std::shared_ptr<EntityManager> _entityManager;
            int speed = 1;
            Timeout _timeMove;
            double _time = 0.003;

    };
}