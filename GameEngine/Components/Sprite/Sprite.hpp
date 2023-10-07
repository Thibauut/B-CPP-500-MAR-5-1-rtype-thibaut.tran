/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Render.hpp
*/

#pragma once
#include "../AComponent/AComponent.hpp"

namespace GameEngine {

    class Sprite : public IComponent {
        public:
            Sprite(CONFIG::CompType type, int id, int spriteIndex, int x, int y) 
            : _idComponent(id), _type(type), _spriteIndex(spriteIndex),  _x(x), _y(y) {}

            ~Sprite() = default;

            void setSprite(int spriteIndex, int width, int height) {
                _spriteIndex = spriteIndex;
                _x = width;
                _y = height;
            }

            int getSpriteIndex() {
                return _spriteIndex;
            }

            int getSpriteX() {
                return _x;
            }

            int getSpriteY() {
                return _y;
            }
            template<class Archive>
            void serialize(Archive & ar, const unsigned int version) {
                ar & _idComponent;
                ar & _type;
                ar & _spriteIndex;
                ar & _x;
                ar & _y;
            }
            virtual CONFIG::CompType getType() {return _type;};
            virtual void setType(const CONFIG::CompType type) {_type = type;};
            virtual int getId() {return _idComponent;};
            virtual void setId(const int id) { _idComponent = id;};

        protected:
            int _idComponent;
            CONFIG::CompType _type;

        private:
            int _spriteIndex;
            int _x;
            int _y;
    };
}