/*
** EPITECH PROJECT, 2023
** SysAI
** File description:
** SysAI
*/

#pragma once
#include "../ASystem/ASystem.hpp"
#include "../../Components/Position/Position.hpp"
#include "../../Components/AI/AI.hpp"
#include "../../Components/Weapon/Weapon.hpp"
#include <chrono>
#include "../../Utils/Timeout.hpp"

namespace GameEngine {
    class SysAI : public ISystem {
        public:
            SysAI(std::shared_ptr<EntityManager> entityList) : _entities(entityList), _sinusoidalY(false), _stateMobOneY(false), _stateMobOneX(false), isRunning(true) {
                canMoveXMob1 = Timeout(0.01);
                canMoveYMob1 = Timeout(0.001);
                canMoveXMob2 = Timeout(0.001);
                canMoveYMob2 = Timeout(0.001);
            }
            ~SysAI() {};
            bool isAI() { return true; };

            virtual void update() override {
                if (!isRunning) {
                    return;
                }

                for (std::shared_ptr<Entity> &entityPtr : _entities.get()->getEntities()) {
                    std::shared_ptr<AI> aiComponent = entityPtr->getComponentByType<AI>(CONFIG::CompType::AI);
                    if (aiComponent != nullptr) {
                        if (aiComponent->getAiType() == CONFIG::AiType::MOB1) {
                            mobalgo1(entityPtr);
                        }
                        if (aiComponent->getAiType() == CONFIG::AiType::MOB2) {
                            mobalgo2(entityPtr);
                        }
                        if (aiComponent->getAiType() == CONFIG::AiType::BOSS) {
                            mobAlgoBoss(entityPtr);
                        }
                    }
                }
        };

        bool checkClostestToAi(int posxP1, int posxP2, int posxAi) {
            int value1 = posxP1 - posxAi;
            int value2 = posxP2 - posxAi;
            if (value1 < 0)
                value1 = value1 * -1;
            if (value2 < 0)
                value2 = value2 * -1;
            if (value1 < value2)
                return true;
            return false;
        }

        private:
            void mobalgo1(std::shared_ptr<Entity> entity) {
                auto aiComponent = entity->getComponentByType<AI>(CONFIG::CompType::AI);
                auto posComponent = entity->getComponentByType<Position>(CONFIG::CompType::POSITION);
                if (canMoveXMob1.can_execute()) {
                    // posComponent->setPosition(posComponent->getPositionX() - 1, posComponent->getPositionY());
                    if (posComponent->getPositionX() <= 1100)
                        _stateMobOneX = true;
                    else if (posComponent->getPositionX() >= 1830)
                        _stateMobOneX = false;
                    if (!_stateMobOneX)
                        posComponent->setPosition(posComponent->getPositionX() - 1, posComponent->getPositionY());
                    else
                        posComponent->setPosition(posComponent->getPositionX() + 1, posComponent->getPositionY());
                    canMoveXMob1.Start();
                }
                if (canMoveYMob1.can_execute()) {
                    if (posComponent->getPositionY() >= 980)
                    _stateMobOneY = true;
                    else if (posComponent->getPositionY() <= 5)
                        _stateMobOneY = false;
                    if (!_stateMobOneY)
                        posComponent->setPosition(posComponent->getPositionX(), posComponent->getPositionY() + 1);
                    else
                        posComponent->setPosition(posComponent->getPositionX(), posComponent->getPositionY() - 1);
                    canMoveYMob1.Start();
                }
            };
            void mobalgo2(std::shared_ptr<Entity> entity) {
                auto aiComponent = entity->getComponentByType<AI>(CONFIG::CompType::AI);
                auto posComponent = entity->getComponentByType<Position>(CONFIG::CompType::POSITION);
                auto weapComponent = entity->getComponentByType<Weapon>(CONFIG::CompType::WEAPON);
                std::list<std::shared_ptr<Entity>> playerList = _entities.get()->getEntitiesByType(1);
                if (playerList.size() == 1) {

                    _clostestPY = playerList.front().get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPositionY();
                    _clostestPX = playerList.front().get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPositionX();
                    std::cout << "Clostest player Position Y --> " << _clostestPY << std::endl;
                    std::cout << "Clostest player Position X --> " << _clostestPX << std::endl;
                } else {

                    for (std::shared_ptr<Entity> &entity : playerList) {

                        // std::cout << "Player num : " << entity.get()->getId() << std::endl;
                        // std::cout << "Y = " << entity.get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPositionY() << std::endl;
                        // std::cout << "X = " << entity.get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPositionX() << std::endl;
                    }
                }
                if (_clostestPY > posComponent->getPositionY() + 150) {
                    // weapComponent->setShooting(false, 0);
                    if (weapComponent->canShoot()) {
                        weapComponent->setShooting(true, 0);
                    }
                } else if (_clostestPY < posComponent->getPositionY() - 150) {
                    // weapComponent->setShooting(false, 0);
                    if (weapComponent->canShoot()) {
                        weapComponent->setShooting(true, 0);
                    }
                } else if (_clostestPY == posComponent->getPositionY()) {
                    std::cout << "Shooting !" << std::endl;
                }
                if (_clostestPY > posComponent->getPositionY()) {
                    if (canMoveYMob2.can_execute()) {
                        posComponent->setPosition(posComponent->getPositionX(), posComponent->getPositionY() + 1);
                        canMoveYMob2.Start();
                    }
                } else if (_clostestPY < posComponent->getPositionY()) {
                    if (canMoveYMob2.can_execute()) {
                        posComponent->setPosition(posComponent->getPositionX(), posComponent->getPositionY() - 1);
                        canMoveYMob2.Start();
                    }
                }
                if (_clostestPX > posComponent->getPositionX() + 250) {
                    if (canMoveXMob2.can_execute()) {
                        posComponent->setPosition(posComponent->getPositionX() + 1, posComponent->getPositionY());
                        canMoveXMob2.Start();
                    }
                } else if (_clostestPX < posComponent->getPositionX() - 250) {
                    if (canMoveXMob2.can_execute()) {
                        posComponent->setPosition(posComponent->getPositionX() - 1, posComponent->getPositionY());
                        canMoveXMob2.Start();
                    }
                }
                if (_clostestPX < posComponent->getPositionX() + 250 && _clostestPX >= posComponent->getPositionX()) {
                    if (canMoveXMob2.can_execute() && posComponent->getPositionX() > 100) {
                        posComponent->setPosition(posComponent->getPositionX() - 1, posComponent->getPositionY());
                        canMoveXMob2.Start();
                    }
                } else if (_clostestPX > posComponent->getPositionX() - 250 && _clostestPX <= posComponent->getPositionX()) {
                    if (canMoveXMob2.can_execute() && posComponent->getPositionX() < 1820) {
                        posComponent->setPosition(posComponent->getPositionX() + 1, posComponent->getPositionY());
                        canMoveXMob2.Start();
                    }
                }
                // if (_clostestPY < posComponent->getPositionY() + 150 && _clostestPY >= posComponent->getPositionY()) {
                //     if (canMoveYMob2.can_execute() && posComponent->getPositionY() > 100) {
                //         posComponent->setPosition(posComponent->getPositionX(), posComponent->getPositionY() - 1);
                //         canMoveYMob2.Start();
                //     }
                // } else if (_clostestPY > posComponent->getPositionY() - 150 && _clostestPY <= posComponent->getPositionY()) {
                //     if (canMoveYMob2.can_execute() && posComponent->getPositionY() > 980) {
                //         posComponent->setPosition(posComponent->getPositionX(), posComponent->getPositionY() + 1);
                //         canMoveYMob2.Start();
                //     }
                // }
                std::cout << "Mob X --> " << posComponent->getPositionX() << std::endl;
                std::cout << "Mob Y --> " << posComponent->getPositionY() << std::endl;
            };
            void mobAlgoBoss(std::shared_ptr<Entity> entity) {
                auto aiComponent = entity->getComponentByType<AI>(CONFIG::CompType::AI);
                auto posComponent = entity->getComponentByType<Position>(CONFIG::CompType::POSITION);
                auto weapComponent = entity->getComponentByType<Weapon>(CONFIG::CompType::WEAPON);
                auto weapBossComponent = entity->getComponentByType<Weapon>(CONFIG::CompType::WEAPON);
                std::list<std::shared_ptr<Entity>> playerList = _entities.get()->getEntitiesByType(1);
                for (std::shared_ptr<Entity> &entity : playerList) {
                    if (entity->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPositionY() <= posComponent->getPositionY() + 150 && entity->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPositionY() >= posComponent->getPositionY() - 150) {
                        std::cout << "In front shooting ! " << std::endl;
                        if (weapBossComponent->canShoot()) {
                            weapBossComponent->setShooting(true, 0);
                        }
                    } else {
                        std::cout << "NOT In front shooting ! " << std::endl;
                        if (weapComponent->canShoot()) {
                            weapComponent->setShooting(true, 0);
                        }
                    }
                }
            };
            Timeout canMoveXMob1;
            Timeout canMoveYMob1;
            Timeout canMoveXMob2;
            Timeout canMoveYMob2;
            bool _sinusoidalY;
            int _basicPositionY;
            int _basicPositionX;
            int _clostestPY;
            int _clostestPX;
            bool _cmpr;
            bool _stateMobOneY;
            bool _stateMobOneX;
            bool isRunning;
            std::shared_ptr<EntityManager> _entities;
 };
 };