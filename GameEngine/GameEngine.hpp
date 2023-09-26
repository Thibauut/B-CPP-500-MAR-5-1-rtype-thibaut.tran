/*
** EPITECH PROJECT, 2023
** GameEngine
** File description:
** GameEngine
*/

#pragma once

#include "Entity/EntityManager/EntityManager.hpp"
#include "Systems/ASystem/ASystem.hpp"
#include <iostream>
#include <memory>
#include <list>


namespace GameEngine {

    class Engine {
        public:
            Engine() {_isRunning = false;}
            ~Engine() {}

            void init() {
                _isRunning = false;
            }

            void run() {
                _isRunning = true;
                while (_isRunning) {
                    for (auto& _system : _systems) {
                        _system->update();
                    }
                }
            }

            void stop() {
                _isRunning = false;
            }

            void addSystem(std::shared_ptr<ASystem> system) {
                _systems.push_back(system);
            }

            void removeSystem(std::shared_ptr<ASystem> system) {
                _systems.remove(system);
            }

        private:
            bool _isRunning;
            EntityManager _entityManager;
            std::list<std::shared_ptr<ASystem>> _systems;
    };

}
