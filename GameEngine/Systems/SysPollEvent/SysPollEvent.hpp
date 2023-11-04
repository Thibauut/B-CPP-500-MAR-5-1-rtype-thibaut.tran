/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** SysPollEvent.hpp
*/

#pragma once

#include "../ASystem/ASystem.hpp"
#include "../../Utils/Utils.hpp"
#include "../../Components/Event/Event.hpp"
#include "../../Components/Window/Window.hpp"

namespace GameEngine {
    class SysPollEvent : public ISystem {
        public:
            SysPollEvent(std::shared_ptr<EntityManager> entityManagerPtr, std::shared_ptr<StateManager> isRunning) : _entityManager(entityManagerPtr), _is_running(isRunning) {};
            virtual ~SysPollEvent() = default;

            virtual void update() {
                std::shared_ptr<Window> win = nullptr;
                for (auto &entity : _entityManager->getEntities())
                    if (entity->getComponentByType<Window>(CONFIG::CompType::WINDOW) != nullptr)
                        win = entity->getComponentByType<Window>(CONFIG::CompType::WINDOW);
                if (win == nullptr)
                    return;
                sf::Event event;
                sf::Vector2i mouse = sf::Mouse::getPosition();
                while (win->getWindow()->pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        win->getWindow()->close();
                    for (auto &entity : _entityManager->getEntities()) {
                        std::vector<std::shared_ptr<Event>> eventComponents = entity->getComponentsByType<Event>(CONFIG::CompType::EVENT);
                        for (auto &eventComponent : eventComponents) {
                            if (eventComponent != nullptr) {
                                Event::event_data data = { _entityManager, entity, &event, mouse, _is_running };
                                eventComponent->run(data);
                            }
                        }
                    }
                }
            }

        private:
            std::shared_ptr<EntityManager> _entityManager;
            std::shared_ptr<StateManager> _is_running;
    };
}