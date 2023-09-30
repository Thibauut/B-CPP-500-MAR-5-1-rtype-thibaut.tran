/*
** EPITECH PROJECT, 2023
** SysRender
** File description:
** SysRender
*/

#pragma once
#include "../ASystem/ASystem.hpp"
#include "../../Utils/Utils.hpp"

namespace GameEngine {

    class SysRender : public ISystem {
        public:
            SysRender(std::shared_ptr<EntityManager> entityManagerPtr) : _entityManager(entityManagerPtr) {};
            virtual ~SysRender() = default;

            virtual void update() {
                // std::cout << "SysRender update" << std::endl;

                // for (auto &entity : _entityManager->getEntities()) {
                //     std::shared_ptr<Sprite> sprite;
                //     std::shared_ptr<Position> pos;

                //     if (entity.get()->getComponentByType<Sprite>(CONFIG::CompType::SPRITE) != nullptr) {
                //         sprite = entity.get()->getComponentByType<Sprite>(CONFIG::CompType::SPRITE);
                //     }
                //     if (entity.get()->getComponentByType<Position>(CONFIG::CompType::POSITION) != nullptr) {
                //         pos = entity.get()->getComponentByType<Position>(CONFIG::CompType::POSITION);
                //     }

                //     if (sprite != nullptr && pos != nullptr) {
                //         int x = sprite.get()->getSpriteX();
                //         int y = sprite.get()->getSpriteY();
                //         int index = sprite.get()->getSpriteIndex();
                //         int posX = pos.get()->getPositionX();
                //         int posY = pos.get()->getPositionY();
                //     }
                // }
            }
        
        private:
            std::shared_ptr<EntityManager> _entityManager;

    };

}