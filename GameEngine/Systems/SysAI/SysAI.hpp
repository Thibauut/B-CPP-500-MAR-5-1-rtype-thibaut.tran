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
            SysAI(std::list<std::shared_ptr<Entity>> &entityList) : _entities(entityList), isRunning(true) {}
            ~SysAI() {};
            bool isAI() { return true; };

            virtual void update() override {
                if (!isRunning) {
                    return;
                }

                for (std::shared_ptr<Entity> &entityPtr : _entities) {
                    std::shared_ptr<AI> aiComponent = entityPtr->getComponentByType<AI>(CONFIG::CompType::AI);
                    if (aiComponent != nullptr) {
                        if (aiComponent->getAiType() == CONFIG::AiType::MOB1) {
                            mobalgo1(entityPtr);
                        }
                    }
                }
        };

        private:
            void mobalgo1(std::shared_ptr<Entity> entity) {
                auto aiComponent = entity->getComponentByType<AI>(CONFIG::CompType::AI);
                auto posComponent = entity->getComponentByType<Position>(CONFIG::CompType::POSITION);
                if (aiComponent->canMove()) {
                    posComponent->setPosition(posComponent->getPositionX() - 1, posComponent->getPositionY());
                    aiComponent->resetCooldown();
                }
            };
            bool isRunning;
            std::list<std::shared_ptr<Entity>> _entities;
    };

}