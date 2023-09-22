/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Position.hpp
*/

#pragma once

class Position {
    public:
        Position(int x, int y) : _x(x), _y(y) {};
        ~Position() {};

        int getX() const { return _x; };
        int getY() const { return _y; };

        void setX(int x) { _x = x; };
        void setY(int y) { _y = y; };

    protected:
        int _x;
        int _y;
};