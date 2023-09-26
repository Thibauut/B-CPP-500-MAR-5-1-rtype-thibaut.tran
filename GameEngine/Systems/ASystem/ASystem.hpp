/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** ASystem.hpp
*/

#pragma once
#include "../../Interfaces/ISystem/ISystem.hpp"
#include "../../Entity/Entity.hpp"


namespace GameEngine {

    class ASystem : public ISystem {
        public:
            ASystem(std::list<std::shared_ptr<Entity>> &entityRef) : _entityRefList(entityRef){}
            virtual ~ASystem() = default;

            virtual void update() {};

        protected:
            std::list<std::shared_ptr<Entity>> &_entityRefList;

        private:
    };
}