/*
** EPITECH PROJECT, 2023
** Strenght
** File description:
** Strenght
*/

#pragma once
#include "../AComponent/AComponent.hpp"

namespace GameEngine {

    template <class T>
    class Strenght : public AComponent {
        public:
            Strenght() {}
            ~Strenght() = default;

            void setComponent() {
                std::cout << "Component : {strenght.set}" << std::endl;
            }

            void setDamage(int damage) {
                _damage = damage;
                std::cout << "Strength setter: damage = " << _damage << std::endl;
            }

            int getDamage() const {
                std::cout << "Strenght getter : return =" << _damage << std::endl;
                return _damage;
            }
        protected:
            int _idComponent;
            int _type;

        private:
            int _damage;
    };
}
