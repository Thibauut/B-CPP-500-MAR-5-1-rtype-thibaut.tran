/*
** EPITECH PROJECT, 2023
** Position
** File description:
** Position
*/

#pragma once

#include "../AComponent/AComponent.hpp"

namespace GameEngine {

    class Position : public AComponent {
        public:
            Position(int type, int id, int x, int y) : AComponent(id), _idComponent(id), _type(type), _xPos(x), _yPos(y) {}
            ~Position() = default;

            void setPostion(int xPos, int yPos) {
                _xPos = xPos;
                _yPos = yPos;
            }

            std::pair<int, int> getPosition() const {
                return std::make_pair(_xPos, _yPos);
            }

            virtual int getType() {return _type;};
            virtual void setType(const int type) {_type = type;};
            virtual int getId() {return _idComponent;};
            virtual void setId(const int id) {_idComponent = id;};

        protected:
            int _idComponent;
            int _type;

        private:
            int _xPos;
            int _yPos;
    };
}
