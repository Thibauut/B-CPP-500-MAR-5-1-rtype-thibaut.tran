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
                Weapon(CONFIG::CompType type, int id, double coulDown, double xSpeed, double ySpeed, double posX, double posY) 
                : _idComponent(id), _type(type), _coulDown(coulDown), _xSpeed(xSpeed), _ySpeed(ySpeed), _posX(posX), _posY(posY)  {}
                ~Weapon() = default;

                void setWeapon(double couldDown, double xSpeed, double ySpeed, double posX, double posY) {
                    _coulDown = couldDown;
                    _xSpeed = xSpeed;
                    _ySpeed = ySpeed;
                    _posX = posX;
                    _posY = posY;
                }

                virtual CONFIG::CompType getType() {return _type;};
                virtual void setType(const CONFIG::CompType type) {_type = type;};
                virtual int getId() {return _idComponent;};
                virtual void setId(const int id) {_idComponent = id;};

            protected:
                int _idComponent;
                CONFIG::CompType _type;

            private:
                double _coulDown;
                double _xSpeed;
                double _ySpeed;
                double _posX;
                double _posY;
        };
    }