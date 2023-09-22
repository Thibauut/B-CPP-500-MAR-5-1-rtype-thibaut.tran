/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Entity.hpp
*/

#pragma once
#include <memory>
#include <list>

#include "../Interfaces/IComponent.hpp"

namespace GameEngine {

    class Entity {
        public:

            Entity(unsigned int id) : _id(id) {};
            ~Entity() {
                for (const auto& component : _entityContent) {
                    component->~IComponent();
                }
            }

            unsigned int getId() const {
                return _id;
            }

            template <class T>
            std::shared_ptr<T> addComponent(std::shared_ptr<IComponent> component) {
                auto desiredComponent = std::dynamic_pointer_cast<T>(component);
                if (desiredComponent) {
                    _entityContent.push_back(desiredComponent);
                    return desiredComponent;
                }
                return nullptr;
            }

            template <class T>
            std::shared_ptr<T> getComponent() {
                for (const auto& component : _entityContent) {
                    if (std::dynamic_pointer_cast<T>(component)) {
                        return std::dynamic_pointer_cast<T>(component);
                    }
                }
                return nullptr;
            }

            void update() {
                for (const auto& component : _entityContent) {
                    component->update();
                }
            }

        private:
            std::list<std::shared_ptr<GameEngine::IComponent>> _entityContent;
            unsigned int _id;
    };
}