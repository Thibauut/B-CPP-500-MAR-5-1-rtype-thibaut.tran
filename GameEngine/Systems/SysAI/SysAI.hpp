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
            SysAI(std::list<std::shared_ptr<Entity>> &entityList) : _entities(entityList) {}
            ~SysAI() {};
            bool isAI() { return true; };

            virtual void update() override {
                // Logique AI (à implémenter)
                if (!isRunning) {
                    return;
                }

                for (std::shared_ptr<Entity>& entityPtr : _entities) {
                    auto aiComponent = entityPtr->getComponentByType<AI>(CONFIG::CompType::AI);

                    if (!aiComponent) {
                        std::cout << "No AI component found on this entity." << '\n';
                    } else if (aiComponent->getAiType() == CONFIG::AiType::MOB1) {
                        mobalgo1(entityPtr);
                    }
                    }
                };

        private:
            void mobalgo1(std::shared_ptr<Entity> &entity) {
                auto aiComponent = entity->getComponentByType<AI>(CONFIG::CompType::AI);
                auto posComponent = entity->getComponentByType<Position>(CONFIG::CompType::POSITION);
                Timeout couldown(aiComponent->getCouldown());
                if (couldown.can_execute() == true) {
                    posComponent->setPosition(posComponent->getPositionX() - 1, posComponent->getPositionY());
                    couldown.Start();
                }
            };
            bool isRunning;
            std::list<std::shared_ptr<Entity>> &_entities;
    };

}