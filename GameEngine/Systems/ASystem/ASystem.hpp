/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** ASystem.hpp
*/

#pragma once
#include "../Interfaces/ISystem.hpp"


namespace GameEngine {

    template <class T>
    class ASystem : public ISystem {
        public:

            virtual void run() override {
            }



        protected:
            std::list<std::shared_ptr<Entity>> _entityRefList;

        private:
    };
}