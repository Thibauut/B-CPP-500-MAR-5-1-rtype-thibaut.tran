/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** EntityManager.hpp
*/

#pragma once

#include "../Entity.hpp"

namespace GameEngine {

    class EntityManager {
        public:
            EntityManager() {}
            ~EntityManager() {}

            void addEntity(Entity entity) {
                std::shared_ptr<Entity> entityPtr = std::make_shared<Entity>(entity);

                _listEntity.push_back(entityPtr);

            }

            std::shared_ptr<Entity>& getEntity(unsigned int id) {
                for (auto& entityPtr : _listEntity) {
                    if (entityPtr->getId() == id) {
                        return entityPtr;
                    }
                }
                throw std::runtime_error("Entity not found");
            }

            void deleteEntity(unsigned int id) {
                for (auto& entityPtr : _listEntity) {
                    if (entityPtr->getId() == id) {
                        _listEntity.remove(entityPtr);
                        return;
                    }
                }
            }

        private:
            std::list<std::shared_ptr<Entity>> _listEntity;
    };

}