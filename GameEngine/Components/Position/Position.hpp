/*
** EPITECH PROJECT, 2023
** Position
** File description:
** Position
*/

#pragma once

#include "../AComponent/AComponent.hpp"

namespace GameEngine {

    template <class T>
    class Position : public AComponenent {
        public:
            Position(int type, int id, int x, int y) : _xPos(x), _yPos(y), _idComponent(id), _type(type) {}
            ~Position() = default;

            void setPostion(int xPos, int yPos) {
                _xPos = xPos;
                _yPos = yPos;
                std::cout << "Position setter : value x, y =" << _xPos << " " << _yPos << std::endl;
            }

            std::pair<int, int> getPosition() const {
                std::cout << "Postion getter : return =" << _xPos << " " << _yPos << std::endl;
                return std::make_pair(_xPos, _yPos);
            }

            virtual int getType() {return _type;};
            virtual void setType(const int type) {_type = type;};
            virtual int getId() {return _id;};
            virtual void setId(const int id) {_id = id;};

        protected:
            int _idComponent;
            int _type;

        private:
            int _xPos;
            int _yPos;
    };
}
