/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Entity.hpp
*/

#pragma once
#include <memory>
#include <list>
#include "../Components/AComponent/AComponent.hpp"
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/list.hpp>

using namespace GameEngine;

namespace GameEngine {
    class Entity {
        public:
            Entity(){}
            Entity(unsigned int id, int type) : _id(id), _entityType(type) {}
            Entity(unsigned int id) : _id(id), _entityType(0) {}

            ~Entity() {}

            template <class Archive>
            void serialize(Archive & ar, const unsigned int version) {
                ar & _id;
                ar & _entityType;
                ar & _entityContent;
            }

            unsigned int getId() const {
                return _id;
            }

            template <typename T>
            void addComponent(T &component) {
                _entityContent.push_back(component);
            }

            template <typename T>
            void deleteComponent(std::shared_ptr<T> component) {
                _entityContent.remove(component);
            }

            template <typename T>
            std::shared_ptr<T> getComponentByType(CONFIG::CompType type) {
                for (auto &component : _entityContent) {
                    if (component.get()->getType() == type)
                        return std::dynamic_pointer_cast<T>(component);
                }
                return nullptr;
            }
            template <typename T>
            std::vector<std::shared_ptr<T>> getComponentsByType(CONFIG::CompType type) {
                std::vector<std::shared_ptr<T>> components;
                for (std::shared_ptr<T> &component : _entityContent) {
                    if (component.get()->getType() == type)
                        components.push_back(component);
                }
                if (!components.empty())
                    return components;
                return nullptr;
            }

            template <typename T>
            std::shared_ptr<T> getComponentById(int id) {
                for (auto &component : _entityContent) {
                    if (component.get()->getId() == id)
                        return component;
                }
                return nullptr;
            }

            std::list<std::shared_ptr<AComponent>> &getComponents() {
                return _entityContent;
            }

            void setEntityContent(std::list<std::shared_ptr<AComponent>> &entity) {
                _entityContent = entity;
            }

            void setType(int type) {
                _entityType = type;
            }

            int getType() const {
                return _entityType;
            }

            void setId(unsigned int id) {
                _id = id;
            }

        private:
            std::list<std::shared_ptr<AComponent>> _entityContent;
            unsigned int _id;
            int _entityType;
    };
}