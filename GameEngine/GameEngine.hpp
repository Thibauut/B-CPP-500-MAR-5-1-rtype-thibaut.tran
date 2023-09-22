/*
** EPITECH PROJECT, 2023
** GameEngine
** File description:
** GameEngine
*/

#pragma once

#include "Interfaces/ISystem.hpp"
#include "Interfaces/IComponent.hpp"
#include "Entity/Entity.hpp"
#include "Entity/EntityManager.hpp"

namespace GameEngine {

    class Engine {
    public:
        Engine() {};
        ~Engine() {};

        void init() {
            isRunning = true;
        }

        void run() {
            while (isRunning) {
              
            }
        }

        void stop() {
            // Nettoyage et arrêt du jeu
        }

    private:
        bool isRunning;

        EntityManager entityManager;
        std::list<std::shared_ptr<ISystem>> systems;
    };

}