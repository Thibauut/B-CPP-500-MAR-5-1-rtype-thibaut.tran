/*
** EPITECH PROJECT, 2023
** SysRender
** File description:
** SysRender
*/

#pragma once
#include "../ASystem/ASystem.hpp"
#include "../../Utils/Utils.hpp"
#include "../../Components/Menu/Menu.hpp"

namespace GameEngine {

    class SysRender : public ISystem {
        public:
            SysRender(std::shared_ptr<EntityManager> entityManagerPtr, CONFIG::Interfaces type) : _entityManager(entityManagerPtr), _type(type) {};
            virtual ~SysRender() = default;

            virtual void update() {
                if (_type == CONFIG::Interfaces::MENUDRAW) {
                    for (std::shared_ptr<Entity>& entity : _entityManager->getEntities()) {
                        std::shared_ptr<MenuComp> menuComp = entity->getComponentByType<MenuComp>(CONFIG::CompType::MENU);
                            // client->gameEngine_.addSystem(std::make_shared<SysRender>(client->gameEngine_.getManager())
                        menuComp->menuRun();
                    }
                }
                else if (_type == CONFIG::Interfaces::GAMEDRAW) {

                }
            }

        private:
            std::shared_ptr<EntityManager> _entityManager;
            CONFIG::Interfaces _type;

    };

}