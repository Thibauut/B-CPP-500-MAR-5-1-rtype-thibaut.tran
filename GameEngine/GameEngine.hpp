/*
** EPITECH PROJECT, 2023
** GameEngine
** File description:
** GameEngine
*/

#pragma once

#include "Entity/EntityManager/EntityManager.hpp"
#include "Components/Position/Position.hpp"
#include "Components/Health/Health.hpp"
#include "Components/AI/AI.hpp"
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
                // _isRunning = true;
                // while (_isRunning) {
                //     for (auto& _system : _systems) {
                //         _system->update();
                //     }
                // }

                // Check value in player's components
                int pos_x = _manager.getEntity(1).get()->getComponentByType<Position>(2).get()->getPosition().first;
                int pos_y = _manager.getEntity(1).get()->getComponentByType<Position>(2).get()->getPosition().second;

                std::cout << "    💜 Player's health: " << std::to_string(_manager.getEntity(1).get()->getComponentByType<Health>(1).get()->getHealth()) << std::endl;
                std::cout << "    👀 Player's position: " << std::to_string(pos_x) << " " << std::to_string(pos_y)  << std::endl;
                std::cout << "🗡  Player take 33 damages 🗡 " << std::endl;

                // Maybe a future system ?
                _manager.getEntity(2).get()->getComponentByType<Health>(1).get()->setHealth(_manager.getEntity(1).get()->getComponentByType<Health>(1).get()->getHealth() - 33);

                std::cout << "    💜 Player's health: " << std::to_string(_manager.getEntity(1).get()->getComponentByType<Health>(1).get()->getHealth()) << std::endl;
                std::cout << "    👀 Player's position: " << std::to_string(pos_x) << " " << std::to_string(pos_y)  << std::endl;
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
