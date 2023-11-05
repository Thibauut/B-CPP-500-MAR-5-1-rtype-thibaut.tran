/*
** EPITECH PROJECT, 2023
** SysRender
** File description:
** SysRender
*/

#pragma once
#include "../ASystem/ASystem.hpp"
#include "../../Utils/Utils.hpp"
#include "../../Components/Position/Position.hpp"
#include "../../Components/Cooldown/Cooldown.hpp"
#include "../../Components/AI/AI.hpp"



namespace GameEngine {

    class SysAIPong : public ISystem {
        public:
            SysAIPong(std::shared_ptr<EntityManager> entityManagerPtr) : _entityManager(entityManagerPtr) {};
            virtual ~SysAIPong() = default;

            virtual void update() {
                for (std::shared_ptr<Entity>& entity : _entityManager->getEntities()) {
                    if (entity->getType() == 2 && entity->getComponentByType<AI>(CONFIG::CompType::AI) != nullptr) {
                        std::shared_ptr<AI> aiComponent = entity->getComponentByType<AI>(CONFIG::CompType::AI);
                        if (aiComponent->getAiType() == CONFIG::AiType::PLAYER) {
                            std::shared_ptr<Entity> posBall = _entityManager->getEntityByType(3);
                            std::shared_ptr<Position> positionComponent = entity->getComponentByType<Position>(CONFIG::CompType::POSITION);
                            std::shared_ptr<Cooldown> cooldown = entity->getComponentByType<Cooldown>(CONFIG::CompType::TIMECOMP);
                            cooldown->create(0.001, "canMoveY");

                            if (posBall != nullptr && positionComponent != nullptr && cooldown->isFinish("canMoveY")) {
                                std::pair<int, int> posBallPair = posBall->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPosition();
                                std::pair<int, int> posPlayerPair = positionComponent->getPosition();
                                if (posBallPair.second < posPlayerPair.second && posPlayerPair.second > 0) {
                                    positionComponent->setPosition(posPlayerPair.first, posPlayerPair.second - 1);
                                }
                                if (posBallPair.second > posPlayerPair.second && posPlayerPair.second < 1080 - 250) {
                                    positionComponent->setPosition(posPlayerPair.first, posPlayerPair.second + 1);
                                }
                                cooldown->reset("canMoveY");
                            }
                        }
                    }
                }
            }

        private:
            std::shared_ptr<EntityManager> _entityManager;
    };

}