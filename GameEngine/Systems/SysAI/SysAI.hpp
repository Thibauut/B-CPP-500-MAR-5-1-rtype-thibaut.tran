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
#include <chrono>
#include "../../Utils/Timeout.hpp"

namespace GameEngine {
    class SysAI : public ISystem {
        public:
            SysAI(std::shared_ptr<EntityManager> entityList) : _entities(entityList), _sinusoidalY(false), _stateMobOneY(false), _stateMobOneX(false), isRunning(true) {
                canMoveX = Timeout(0.01);
                canMoveY = Timeout(0.001);
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
                    }
                }
        };

        private:
            void mobalgo1(std::shared_ptr<Entity> entity) {
                auto aiComponent = entity->getComponentByType<AI>(CONFIG::CompType::AI);
                auto posComponent = entity->getComponentByType<Position>(CONFIG::CompType::POSITION);
                if (canMoveX.can_execute()) {
                    // posComponent->setPosition(posComponent->getPositionX() - 1, posComponent->getPositionY());
                    if (posComponent->getPositionX() <= 1100)
                        _stateMobOneX = true;
                    else if (posComponent->getPositionX() >= 1830)
                        _stateMobOneX = false;
                    if (!_stateMobOneX)
                        posComponent->setPosition(posComponent->getPositionX() - 1, posComponent->getPositionY());
                    else
                        posComponent->setPosition(posComponent->getPositionX() + 1, posComponent->getPositionY());
                    canMoveX.Start();
                }
                if (canMoveY.can_execute()) {
                    if (posComponent->getPositionY() >= 980)
                    _stateMobOneY = true;
                    else if (posComponent->getPositionY() <= 5)
                        _stateMobOneY = false;
                    if (!_stateMobOneY)
                        posComponent->setPosition(posComponent->getPositionX(), posComponent->getPositionY() + 1);
                    else
                        posComponent->setPosition(posComponent->getPositionX(), posComponent->getPositionY() - 1);
                    canMoveY.Start();
                }
            };
            void mobalgo2(std::shared_ptr<Entity> entity) {
                auto aiComponent = entity->getComponentByType<AI>(CONFIG::CompType::AI);
                auto posComponent = entity->getComponentByType<Position>(CONFIG::CompType::POSITION);

            };
            Timeout canMoveX;
            Timeout canMoveY;
            bool _sinusoidalY;
            int _basicPositionY;
            int _basicPositionX;
            bool _stateMobOneY;
            bool _stateMobOneX;
            bool isRunning;
            std::shared_ptr<EntityManager> _entities;
 };
 };