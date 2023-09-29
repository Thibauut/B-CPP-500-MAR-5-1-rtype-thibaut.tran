/*
** EPITECH PROJECT, 2023
** direction
** File description:
** Direction
*/

#pragma once

#include "../AComponent/AComponent.hpp"

namespace GameEngine {

    class Direction : public IComponent {
        public:
            Direction(CONFIG::CompType type, CONFIG::Dir dir) : _type(type), _dir(dir) {}
            ~Direction() = default;

            void setDirection(CONFIG::Dir direction) {
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
