/*
** EPITECH PROJECT, 2023
** Strenght
** File description:
** Strenght
*/

#pragma once
#include "AComponent.hpp"

namespace GameEngine {

    class Strenght : public GameEngine::AComponenent {
        public:
            Strenght() {};
            ~Strenght() = default;
            
            void setComponent() {
                std::cout << "Component : {strenght.set}" << std::endl;
            };

            void setDamage(int damage) {
                _damage = damage;
                std::cout << "Strength setter: damage = " << _damage << std::endl;
            }

            int getDamage() const {
                std::cout << "Strenght getter : return =" << _damage << std::endl;
                return _damage;
            }

    
        private:
            int _damage;
    };
}
