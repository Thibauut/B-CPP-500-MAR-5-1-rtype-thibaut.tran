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

using namespace GameEngine;

namespace GameEngine {
    class Entity {
        public:

            Entity(unsigned int id) : _id(id) {}

            ~Entity() {}

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
            std::shared_ptr<T> getComponentByType(int type) {
                for (auto &component : _entityContent) {
                    if (component.get()->getType() == type)
                        return std::dynamic_pointer_cast<T>(component);
                }
                return nullptr;
            }

            template <typename T>
            std::shared_ptr<T> getComponentById(int id) {
                for (auto &component : _entityContent) {
                    if (component->getId() == id)
                        return component;
                }
                return nullptr;
            }

            template <typename T>
            std::list<std::shared_ptr<T>> &getComponents() {
                return _entityContent;
            }

        private:
            std::list<std::shared_ptr<IComponent>> _entityContent;
            unsigned int _id;

    };
}