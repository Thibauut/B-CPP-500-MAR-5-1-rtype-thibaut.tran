/*
** EPITECH PROJECT, 2023
** Weapon
** File description:
** Weapon
*/

#pragma once
    #include "../AComponent/AComponent.hpp"

    namespace GameEngine {
        class Weapon : public IComponent {
            public:
                Weapon(CONFIG::CompType type, CONFIG::Dir dir) : _type(type), _dir(dir) {};
                ~Weapon() = default;

                void setWeapon(CONFIG::Dir direction) {
                    _dir = direction;
                }

                virtual CONFIG::CompType getType() {return _type;};
                virtual void setType(const CONFIG::CompType type) {_type = type;};
                virtual int getId() {return _idComponent;};
                virtual void setId(const int id) {_idComponent = id;};

            protected:
                int _idComponent;
                CONFIG::CompType _type;

            private:
                CONFIG::Dir _dir;
        };
    }