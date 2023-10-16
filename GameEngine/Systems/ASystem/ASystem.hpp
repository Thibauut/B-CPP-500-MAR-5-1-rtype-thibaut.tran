/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** ASystem.hpp
*/

#pragma once
#include "../../Interfaces/ISystem/ISystem.hpp"
#include "../../Entity/EntityManager/EntityManager.hpp"
#include "../../Entity/Entity.hpp"


namespace GameEngine {

    class ASystem : public ISystem {
        public:
            ASystem(std::shared_ptr<EntityManager> entityManagerPtr) : entityManager(entityManagerPtr){}
            virtual ~ASystem() = default;

            virtual void update() {};

        protected:
           std::shared_ptr<EntityManager> entityManager;

        private:
    };
}