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
            Health(int type, int id, int value) : _hp(value), _type(type), _idComponent(id) {}
            ~Health() = default;

            bool decrementHealth(int damage) {
                if (_hp <= 0)
                    return false;
                std::cout << "Health--" << _hp << std::endl;
                _hp -= damage;
                return true;
            }

            void setHealth(int hp) {
                _hp = hp;
                std::cout << "Health setter : value =" << _hp << std::endl;
            }

            int getHealth() const {
                std::cout << "Health getter : return =" << _hp << std::endl;
                return _hp;
            }

            virtual int getType() {return _type;};
            virtual void setType(const int type) {_type = type;};
            virtual int getId() {return _id;};
            virtual void setId(const int id) {_id = id;};

        protected:
            int _idComponent;
            int _type;

        private:
            int _hp;
    };
}
