/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** EntityManager.hpp
*/

#pragma once

#include "Entity.hpp"

namespace GameEngine {

    class EntityManager {
        public:
            EntityManager() {}
            ~EntityManager() {}

            std::shared_ptr<GameEngine::Entity>& addEntity(Entity entity) {
                std::shared_ptr<Entity> entityPtr = std::make_shared<Entity>(entity);

                _listEntity.push_back(entityPtr);

                return _listEntity.back();
            }

            std::shared_ptr<GameEngine::Entity>& getEntity(unsigned int id) {
                for (auto& entityPtr : _listEntity) {
                    if (entityPtr->getId() == id) {
                        return entityPtr;
                    }
                }
                static std::shared_ptr<Entity> nullEntity;
                return nullEntity;
            }

            void killEntity(unsigned int id) {
                auto it = _listEntity.begin();
                while (it != _listEntity.end()) {
                    if ((*it)->getId() == id) {
                        it = _listEntity.erase(it);
                    } else {
                        ++it;
                    }
                }
            }


        private:
            std::list<std::shared_ptr<GameEngine::Entity>> _listEntity;
    };

}