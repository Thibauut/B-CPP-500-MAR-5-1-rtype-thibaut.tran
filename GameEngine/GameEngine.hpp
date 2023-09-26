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
            Engine(EntityManager manager) : _manager(manager) {_isRunning = false;}
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

            EntityManager _manager;
        private:
            bool _isRunning;
            std::list<std::shared_ptr<ASystem>> _systems;
    };

}
