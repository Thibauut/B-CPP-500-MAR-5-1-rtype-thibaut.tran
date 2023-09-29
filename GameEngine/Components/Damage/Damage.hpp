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
    class Damage : public AComponent {
        public:
            Damage(CONFIG::CompType type, int id, int damage) { _type(type), _id(id), _damage = 1;}
            ~Damage() = default;
            void setDamage(int new_damage){ _damage = new_damage;}

            virtual CONFIG::CompType getType() {return _type;};
            virtual void setType(const CONFIG::CompType type) {_type = type;};
            virtual int getId() {return _id;};
            virtual void setId(const int id) {return id;};

        protected:
            int _idComponent;
            CONFIG::CompType _type;

        private:
            int _damage;
    };
}