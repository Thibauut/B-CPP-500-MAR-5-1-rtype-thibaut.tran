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
    class Hitbox : public AComponent {
        public:
            Hitbox(CONFIG::CompType type, int id, int width, int height) { _type(type), _id(id),  _width(width), _height(height);}
            ~Hitbox() = default;

            void setHitbox(int new_width, int new_height){ _width = new_width, _height = new_height;}

            std::pair getHitbox() {
                std::pair<int, int> ret;
                ret.first = _width;
                ret.second = height;
                return ret;
            }

            int getWidth(){return _width;}
            int getHeight(){return _height;}

            virtual CONFIG::CompType getType() {return _type;};
            virtual void setType(const CONFIG::CompType type) {_type = type;};
            virtual int getId() {return _id;};
            virtual void setId(const int id) {return id;};

        protected:
            int _idComponent;
            CONFIG::CompType _type;

        private:
            int _width;
            int _height;
    };
}