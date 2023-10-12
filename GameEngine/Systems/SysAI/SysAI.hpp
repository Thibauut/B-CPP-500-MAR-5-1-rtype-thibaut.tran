/*
** EPITECH PROJECT, 2023
** SysAI
** File description:
** SysAI
*/

#pragma once
#include "../ASystem/ASystem.hpp"
#include "../../Components/Position/Position.hpp"
#include <chrono>

namespace GameEngine {
    template <class T>
    class SysAI : public ASystem {
        public:
            SysAI(std::list<std::shared_ptr<Entity>> &);
            ~SysAI() {};
            bool isAI() {};

            template <class T>
            virtual void update() override {
                // Logique AI (à implémenter)
                if (!isRunning) {
                    return;
                }

                for (std::shared_ptr<Entity>& entityPtr : EntityManager_) {
                    auto aiComponent = entityPtr->getComponentByType<AI>(CONFIG::CompType::AI);

                    if (!aiComponent) {
                        std::cout << "No AI component found on this entity." << '\n';
                    } else if (aiComponent->getAiType() == CONFIG::AiType::MOB1) {
                        mobalgo1();
                    }
                    }
                };

        private:
            bool mobalgo1() {
                position_ = entityPtr->getComponentByType<Position>(CONFIG::CompType::POSITION);
                position_->setPosition(position_->getPositionX() - 1, position_->setPositionY());
                std::chrono::milliseconds couldown = aiComponent->getCouldown();
                std::time_t current_time = std::chrono::system_clock::to_time_t(now);
                // waiting the couldown time thanks current_time value
                std::time_t limit_time = current_time + couldown;
                while (current_time < limit_time) {
                    current_time = std::chrono::system_clock::to_time_t(now);
                }
            };
            bool isRunning;
            std::list<std::shared_ptr<Entity>> &_entities;
            std::shared_ptr<Position> &position_;
    };

}