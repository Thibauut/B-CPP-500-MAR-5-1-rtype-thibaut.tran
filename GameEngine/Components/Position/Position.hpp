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
            Position() : _xPos(0), _yPos(0) {}
            ~Position() = default;

            void setComponent() {
                std::cout << "Component : {positon.set}" << std::endl;
            }

            void setPostion(int xPos, int yPos) {
                _xPos = xPos;
                _yPos = yPos;
                std::cout << "Position setter : value x, y =" << _xPos << " " << _yPos << std::endl;
            }

            std::pair<int, int> getPosition() const {
                std::cout << "Postion getter : return =" << _xPos << " " << _yPos << std::endl;
                return std::make_pair(_xPos, _yPos);
            }

        private:
            int _xPos;
            int _yPos;
    };
}
