/*
** EPITECH PROJECT, 2023
** Position
** File description:
** Position
*/

#pragma once

#include "../AComponent/AComponent.hpp"

namespace GameEngine {
    class Position : public IComponent {
        public:
            Position(CONFIG::CompType type, int id, int x, int y) : _idComponent(id), _type(type), _xPos(x), _yPos(y) {}
            virtual ~Position() = default;

            void setPosition(int xPos, int yPos) {
                _xPos = xPos;
                _yPos = yPos;
            }

            void setPositionX(int xPos) {
                _xPos = xPos;
            }

            void setPositionY(int yPos) {
                _yPos = yPos;
            }

            std::pair<int, int> getPosition() const {
                return std::make_pair(_xPos, _yPos);
            }

            int getPositionX() {
                return _xPos;
            }

            int getPositionY() {
                return _yPos;
            }

            virtual CONFIG::CompType getType() {return _type;};
            virtual void setType(const CONFIG::CompType type) {_type = type;};
            virtual int getId() {return _idComponent;};
            virtual void setId(const int id) {_idComponent = id;};

        protected:
            int _idComponent;
            CONFIG::CompType _type;

        private:
            int _xPos;
            int _yPos;
    };
}
