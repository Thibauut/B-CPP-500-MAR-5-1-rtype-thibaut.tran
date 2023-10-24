/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** EntityManager.hpp
*/

#pragma once

#include "../Entity.hpp"
#include <mutex>

namespace GameEngine {

    class EntityManager {
        public:
            EntityManager() {}
            EntityManager(EntityManager &entityManager) {
                _listEntity = entityManager.getEntities();
            }
            ~EntityManager() {}

            std::shared_ptr<Entity>& createEntity() {
                _entityPtr = std::make_shared<Entity>(1);
                return _entityPtr;
            }

            std::shared_ptr<Entity>& addEntity(Entity entity) {
                _entityPtr = std::make_shared<Entity>(entity);
                _listEntity.push_back(_entityPtr);
                return _entityPtr;
            }

            std::shared_ptr<Entity>& getEntity(std::string uuid) {
                for (auto& entityPtr : _listEntity) {
                    if (entityPtr->getUuid() == uuid) {
                        return entityPtr;
                    }
                }
                throw std::runtime_error("Entity not found");
            }

            std::shared_ptr<Entity>& getEntityById(unsigned int id) {
                for (auto& entityPtr : _listEntity) {
                    if (entityPtr->getId() == id) {
                        return entityPtr;
                    }
                }
                throw std::runtime_error("Entity not found");
            }

            std::shared_ptr<EntityManager> getEntityManager() {
                return std::make_shared<EntityManager>(*this);
            }

            std::list<std::shared_ptr<Entity>>& getEntities() {
                return _listEntity;
            }

            std::list<std::shared_ptr<Entity>> getEntitiesByType(int entityType) {
                std::list<std::shared_ptr<Entity>> listEntity;
                for (std::shared_ptr<Entity> &entityPtr : _listEntity) {
                    if (entityPtr.get()->getType() == entityType) {
                        listEntity.push_back(entityPtr);
                    }
                }
                return listEntity;
            }

            std::shared_ptr<Entity> getEntityByType(int entityType) {
                for (std::shared_ptr<Entity> &entityPtr : _listEntity) {
                    if (entityPtr.get()->getType() == entityType) {
                        return entityPtr;
                    }
                }
                return nullptr;
            }

            std::mutex &getMutex() {
                return _mutex;
            }

            void deleteEntity(std::string uuid) {
                std::lock_guard<std::mutex> lock(_mutex);
                for (std::shared_ptr<Entity> entityPtr : _listEntity) {
                    if (entityPtr->getUuid() == uuid) {
                        _listEntity.remove(entityPtr);
                        return;
                    }
                }
                // unlock();
            }

            bool try_lock() {
                return _mutex.try_lock();
            }

            void lock() {
                _mutex.lock();
            }

            void unlock() {
                _mutex.unlock();
            }

        private:
            std::list<std::shared_ptr<Entity>> _listEntity;
            std::shared_ptr<Entity> _entityPtr;
            std::mutex _mutex;
    };

}