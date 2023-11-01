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
            SysPollEvent(std::shared_ptr<EntityManager> entityManagerPtr) : _entityManager(entityManagerPtr) {};
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
                        std::shared_ptr<Event> eventComponent = entity->getComponentByType<Event>(CONFIG::CompType::EVENT);
                        if (eventComponent != nullptr) {
                            Event::event_data data = { _entityManager, entity, &event, mouse };
                            eventComponent->run(data);
                        }
                    }
                }
            }

        private:
            std::shared_ptr<EntityManager> _entityManager;
    };
}