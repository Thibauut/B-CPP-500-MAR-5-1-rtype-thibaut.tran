/*
** EPITECH PROJECT, 2023
** GameEngine
** File description:
** GameEngine
*/

#pragma once

#include "Interfaces/IComponent/IComponent.hpp"
#include "Entity/EntityManager/EntityManager.hpp"
#include "Components/Position/Position.hpp"
#include "Components/Velocity/Velocity.hpp"
#include "Components/Health/Health.hpp"
#include "Components/AI/AI.hpp"
#include "Systems/ASystem/ASystem.hpp"
#include "Systems/SysMovement/SysMovement.hpp"
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

                // Check value in player's components
                int pos_x = _manager.getEntity(1).get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPosition().first;
                int pos_y = _manager.getEntity(1).get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPosition().second;

                std::cout << "    💜 Player's health: " << std::to_string(_manager.getEntity(CONFIG::CompType::HEALTH).get()->getComponentByType<Health>(CONFIG::CompType::HEALTH).get()->getHealth()) << std::endl;
                std::cout << "    👀 Player's position: " << std::to_string(pos_x) << " " << std::to_string(pos_y)  << std::endl;
                std::cout << "🗡  Player take 33 damages 🗡 " << std::endl;

                // Maybe a future system ?
                _manager.getEntity(2).get()->getComponentByType<Health>(CONFIG::CompType::HEALTH).get()->setHealth(_manager.getEntity(CONFIG::CompType::HEALTH).get()->getComponentByType<Health>(CONFIG::CompType::HEALTH).get()->getHealth() - 33);

                std::cout << "    💜 Player's health: " << std::to_string(_manager.getEntity(CONFIG::CompType::HEALTH).get()->getComponentByType<Health>(CONFIG::CompType::HEALTH).get()->getHealth()) << std::endl;
                std::cout << "    👀 Player's position: " << std::to_string(pos_x) << " " << std::to_string(pos_y)  << std::endl;
                
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

            std::shared_ptr<EntityManager> getManager() {
                return std::make_shared<EntityManager>(_manager);
            }

            void addSystem(std::shared_ptr<ISystem> system) {
                _systems.push_back(system);
            }

            void removeSystem(std::shared_ptr<ISystem> system) {
                _systems.remove(system);
            }

            EntityManager _manager;
        private:
            bool _isRunning;
            std::list<std::shared_ptr<ISystem>> _systems;
    };

}
