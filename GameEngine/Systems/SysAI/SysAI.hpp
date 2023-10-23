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
#include "../../Components/Direction/Direction.hpp"
#include "../../Components/Cooldown/Cooldown.hpp"

#include <chrono>
#include "../../Utils/Timeout.hpp"

namespace GameEngine {
    class SysAI : public ISystem {
        public:
            SysAI(std::shared_ptr<EntityManager> entityList) : _entities(entityList), _sinusoidalY(false), isRunning(true) {}
            ~SysAI() {};
            bool isAI() { return true; };

            virtual void update() override {
                if (!isRunning) {
                    return;
                }

                for (std::shared_ptr<Entity> &entityPtr : _entities.get()->getEntities()) {
                    std::shared_ptr<AI> aiComponent = entityPtr->getComponentByType<AI>(CONFIG::CompType::AI);
                    std::shared_ptr<Cooldown> couldowComponent = entityPtr->getComponentByType<Cooldown>(CONFIG::CompType::TIMECOMP);
                    if (aiComponent == nullptr || couldowComponent == nullptr)
                        continue;
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
                std::shared_ptr<AI> aiComponent = entity->getComponentByType<AI>(CONFIG::CompType::AI);
                std::shared_ptr<Position> posComponent = entity->getComponentByType<Position>(CONFIG::CompType::POSITION);
                std::shared_ptr<Cooldown> cooldown = entity->getComponentByType<Cooldown>(CONFIG::CompType::TIMECOMP);
                auto weapComponent = entity->getComponentByType<Weapon>(CONFIG::CompType::WEAPON);
                weapComponent->setShooting(false, 0);
                cooldown->create(0.01, "canMoveX");
                cooldown->create(0.001, "canMoveY");
                if (!aiComponent->_setSpawn) {
                    aiComponent->_spawnY = posComponent->getPositionY();
                    aiComponent->_setSpawn = true;
                }
                if (cooldown->isFinish("canMoveX")) {
                    // posComponent->setPosition(posComponent->getPositionX() - 1, posComponent->getPositionY());
                    // if (posComponent->getPositionX() <= 1100)
                        // aiComponent->_stateMobOneX = true;
                    // else if (posComponent->getPositionX() >= 1830)
                        aiComponent->_stateMobOneX = false;
                    if (!aiComponent->_stateMobOneX)
                        posComponent->setPosition(posComponent->getPositionX() - 1, posComponent->getPositionY());
                    else
                        posComponent->setPosition(posComponent->getPositionX() + 1, posComponent->getPositionY());
                    cooldown->reset("canMoveX");
                }
                if (cooldown->isFinish("canMoveY") ) {
                    // posComponent->setPosition(posComponent->getPositionX(), posComponent->getPositionY() + 1);
                    // if (posComponent->getPositionY() >= 980)
                    //     posComponent->setPosition(posComponent->getPositionX(), posComponent->getPositionY() - 1);
                    if (posComponent->getPositionY() >= 980)
                    aiComponent->_stateMobOneY = true;
                    else if (posComponent->getPositionY() <= 5)
                        aiComponent->_stateMobOneY = false;
                    if (!aiComponent->_stateMobOneY)
                        posComponent->setPosition(posComponent->getPositionX(), posComponent->getPositionY() + 1);
                    else
                        posComponent->setPosition(posComponent->getPositionX(), posComponent->getPositionY() - 1);
                    cooldown->reset("canMoveY");
                }
            };
            void mobalgo2(std::shared_ptr<Entity> entity) {
                auto aiComponent = entity->getComponentByType<AI>(CONFIG::CompType::AI);
                auto posComponent = entity->getComponentByType<Position>(CONFIG::CompType::POSITION);
                auto weapComponent = entity->getComponentByType<Weapon>(CONFIG::CompType::WEAPON);
                auto cooldown = entity->getComponentByType<Cooldown>(CONFIG::CompType::TIMECOMP);
                cooldown->create(0.01, "canMoveX");
                cooldown->create(0.01, "canMoveY");
                weapComponent->setShooting(true, 0);
                std::list<std::shared_ptr<Entity>> playerList = _entities.get()->getEntitiesByType(1);
                if (playerList.size() == 1) {
                    _clostestPY = playerList.front().get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPositionY();
                    _clostestPX = playerList.front().get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPositionX();
                    // std::cout << "Clostest player Position Y --> " << _clostestPY << std::endl;
                    // std::cout << "Clostest player Position X --> " << _clostestPX << std::endl;
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
                        // weapComponent->setShooting(true, 0);
                    }
                } else if (_clostestPY < posComponent->getPositionY() - 150) {
                    // weapComponent->setShooting(false, 0);
                    if (weapComponent->canShoot()) {
                        // weapComponent->setShooting(true, 0);
                    }
                } else if (_clostestPY == posComponent->getPositionY()) {
                    // std::cout << "Shooting !" << std::endl;
                }
                if (_clostestPY > posComponent->getPositionY()) {
                    if (cooldown->isFinish("canMoveY")) {
                        posComponent->setPosition(posComponent->getPositionX(), posComponent->getPositionY() + 1);
                        cooldown->reset("canMoveY");
                    }
                } else if (_clostestPY < posComponent->getPositionY()) {
                    if (cooldown->isFinish("canMoveY")) {
                        posComponent->setPosition(posComponent->getPositionX(), posComponent->getPositionY() - 1);
                        cooldown->reset("canMoveY");
                    }
                }
                if (_clostestPX > posComponent->getPositionX() + 250) {
                    if (cooldown->isFinish("canMoveX")) {
                        posComponent->setPosition(posComponent->getPositionX() + 1, posComponent->getPositionY());
                        cooldown->reset("canMoveX");
                    }
                } else if (_clostestPX < posComponent->getPositionX() - 250) {
                    if (cooldown->isFinish("canMoveX")) {
                        posComponent->setPosition(posComponent->getPositionX() - 1, posComponent->getPositionY());
                        cooldown->reset("canMoveX");
                    }
                }
                if (_clostestPX < posComponent->getPositionX() + 450 && _clostestPX >= posComponent->getPositionX()) {
                    if (cooldown->isFinish("canMoveX") && posComponent->getPositionX() > 450) {
                        posComponent->setPosition(posComponent->getPositionX() - 1, posComponent->getPositionY());
                        entity->getComponentByType<Direction>(CONFIG::CompType::DIRECTION)->setDirection(1);
                        cooldown->reset("canMoveX");
                    }
                } else if (_clostestPX > posComponent->getPositionX() - 450 && _clostestPX <= posComponent->getPositionX()) {
                    if (cooldown->isFinish("canMoveX") && posComponent->getPositionX() < 1470) {
                        entity->getComponentByType<Direction>(CONFIG::CompType::DIRECTION)->setDirection(-1);
                        posComponent->setPosition(posComponent->getPositionX() + 1, posComponent->getPositionY());
                        cooldown->reset("canMoveX");
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
                // std::cout << "Mob X --> " << posComponent->getPositionX() << std::endl;
                // std::cout << "Mob Y --> " << posComponent->getPositionY() << std::endl;
            };
            void mobAlgoBoss(std::shared_ptr<Entity> entity) {
                auto aiComponent = entity->getComponentByType<AI>(CONFIG::CompType::AI);
                auto posComponent = entity->getComponentByType<Position>(CONFIG::CompType::POSITION);
                auto weapComponent = entity->getComponentByType<Weapon>(CONFIG::CompType::WEAPON);
                auto weapBossComponent = entity->getComponentByType<Weapon>(CONFIG::CompType::WEAPON);
                std::shared_ptr<Cooldown> cooldown = entity->getComponentByType<Cooldown>(CONFIG::CompType::TIMECOMP);
                std::list<std::shared_ptr<Entity>> playerList = _entities.get()->getEntitiesByType(1);
                cooldown->create(0.03, "canMoveXBoss1");
                cooldown->create(0.003, "canMoveYBoss1");
                if (cooldown->isFinish("canMoveXBoss1")) {
                    // posComponent->setPosition(posComponent->getPositionX() - 1, posComponent->getPositionY());
                    if (posComponent->getPositionX() <= 100)
                        aiComponent->_stateMobOneX = true;
                    else if (posComponent->getPositionX() >= 1820)
                        aiComponent->_stateMobOneX = false;
                    if (!aiComponent->_stateMobOneX)
                        posComponent->setPosition(posComponent->getPositionX() - 1, posComponent->getPositionY());
                    else
                        posComponent->setPosition(posComponent->getPositionX() + 1, posComponent->getPositionY());
                    cooldown->reset("canMoveXBoss1");
                }
                if (cooldown->isFinish("canMoveYBoss1")) {
                    // posComponent->setPosition(posComponent->getPositionX(), posComponent->getPositionY() + 1);
                    // if (posComponent->getPositionY() >= 980)
                    //     posComponent->setPosition(posComponent->getPositionX(), posComponent->getPositionY() - 1);
                    if (posComponent->getPositionY() >= 780)
                    aiComponent->_stateMobOneY = true;
                    else if (posComponent->getPositionY() <= 300)
                        aiComponent->_stateMobOneY = false;
                    if (!aiComponent->_stateMobOneY)
                        posComponent->setPosition(posComponent->getPositionX(), posComponent->getPositionY() + 1);
                    else
                        posComponent->setPosition(posComponent->getPositionX(), posComponent->getPositionY() - 1);
                    cooldown->reset("canMoveYBoss1");
                }
                for (std::shared_ptr<Entity> &entity : playerList) {
                    if (entity->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPositionY() <= posComponent->getPositionY() + 150 && entity->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPositionY() >= posComponent->getPositionY() - 150) {
                        // std::cout << "In front shooting ! " << std::endl;
                        if (weapBossComponent->canShoot()) {
                            weapBossComponent->setShooting(true, 0);
                        }
                    } else {
                        // std::cout << "NOT In front shooting ! " << std::endl;
                        if (weapComponent->canShoot()) {
                            weapComponent->setShooting(true, 0);
                        }
                    }
                }
            };
            bool _sinusoidalY;
            int _basicPositionY;
            int _basicPositionX;
            int _clostestPY;
            int _clostestPX;
            bool _cmpr;
            bool isRunning;
            std::shared_ptr<EntityManager> _entities;
 };
 };