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
            void addComponent(std::shared_ptr<AComponent> component) {
                _entityContent.push_back(component);
            }

            void deleteComponent(std::shared_ptr<AComponent> component) {
                _entityContent.remove(component);
            }

            template <typename T>
            std::shared_ptr<AComponent> getComponentByType(int type) {
                for (auto &component : _entityContent) {
                    if (component->getType() == type)
                        return component;
                }
                return nullptr;
            }

            template <typename T>
            std::shared_ptr<AComponent> getComponentById(int id) {
                for (auto &component : _entityContent) {
                    if (component->getId() == id)
                        return component;
                }
                return nullptr;
            }

            template <typename T>
            std::list<std::shared_ptr<AComponent>> &getComponents() {
                return _entityContent;
            }

        private:
            std::list<std::shared_ptr<AComponent>> _entityContent;
            unsigned int _id;

    };
}