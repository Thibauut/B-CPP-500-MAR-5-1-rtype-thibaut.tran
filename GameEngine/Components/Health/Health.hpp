/*
** EPITECH PROJECT, 2023
** Health
** File description:
** Health
*/

#pragma once

#include "../AComponent/AComponent.hpp"

namespace GameEngine {

    class Health : public IComponent {
        public:
            Health(GameEngine::ListComp type, int id, int value) : _idComponent(id), _type(type), _hp(value)
            {}
            ~Health() = default;

            bool decrementHealth(int damage) {
                if (_hp <= 0)
                    return false;
                _hp -= damage;
                return true;
            }

            void setHealth(int hp) {
                _hp = hp;
            }

            int getHealth() const {
                return _hp;
            }

            virtual GameEngine::ListComp getType() {return _type;};
            virtual void setType(const GameEngine::ListComp type) {_type = type;};
            virtual int getId() {return _idComponent;};
            virtual void setId(const int id) {_idComponent = id;};

        protected:
            int _idComponent;
            GameEngine::ListComp _type;

        private:
            int _hp;
    };
}
