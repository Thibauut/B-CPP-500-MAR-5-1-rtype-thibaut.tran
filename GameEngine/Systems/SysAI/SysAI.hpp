/*
** EPITECH PROJECT, 2023
** SysAI
** File description:
** SysAI
*/

#pragma once
#include "../ASystem/ASystem.hpp"


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

                for (const auto& entityPtr : EntityManager_) {
                    auto aiComponent = entityPtr->getComponent<AI>();

                    if (!aiComponent) {
                        std::cout << "No AI component found on this entity." << '\n';
                    }
                //  if fonction mob
                }


                // if fonction player
            }

        private:
            bool isRunning;
            std::list<std::shared_ptr<Entity>> &_entities;
    };

}