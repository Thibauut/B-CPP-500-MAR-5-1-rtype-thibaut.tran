/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** SysRenderGlobal.hpp
*/

#pragma once
#include "../ASystem/ASystem.hpp"
#include "../../Utils/Utils.hpp"
#include "../../Components/Sprite/Sprite.hpp"
#include "../../Components/Window/Window.hpp"

namespace GameEngine {
    class SysRenderGlobal : public ISystem {
        public:
            SysRenderGlobal(std::shared_ptr<EntityManager> entityManagerPtr) : _entityManager(entityManagerPtr) {};
            virtual ~SysRenderGlobal() = default;

            virtual void update() {
                std::shared_ptr<Window> win = nullptr;
                for (auto &entity : _entityManager->getEntities())
                    if (entity->getComponentByType<Window>(CONFIG::CompType::WINDOW) != nullptr)
                        win = entity->getComponentByType<Window>(CONFIG::CompType::WINDOW);
                if (win == nullptr)
                    return;
                win->clear();
                for (auto &entity : _entityManager->getEntities()) {
                    std::shared_ptr<Sprite> sprite = entity->getComponentByType<Sprite>(CONFIG::CompType::SPRITE);
                    if (sprite != nullptr)
                        win->draw(sprite->getSprite());
                }
                win->display();
            }

        private:
            std::shared_ptr<EntityManager> _entityManager;
    };
}