/*
** EPITECH PROJECT, 2023
** Health
** File description:
** Health
*/

#pragma once

#include "../AComponent/AComponent.hpp"

namespace GameEngine {

    template <class T>
    class Health : public AComponenent {
        public:
            Health() : _hp(100) {}
            ~Health() = default;

            void setComponent() {
                std::cout << "Component : {health.set}" << std::endl;
            }

            void setHealth(int hp) {
                _hp = hp;
                std::cout << "Health setter : value =" << _hp << std::endl;
            }

            int getHealth() const {
                std::cout << "Health getter : return =" << _hp << std::endl;
                return _hp;
            }


        private:
            int _hp;
    };
}
