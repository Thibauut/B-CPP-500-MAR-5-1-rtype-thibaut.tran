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
                Weapon(CONFIG::CompType type, int id, double coolDown, double xSpeed, double ySpeed, double posX, double posY) 
                : _idComponent(id), _type(type), _coolDown(coolDown), _xSpeed(xSpeed), _ySpeed(ySpeed), _posX(posX), _posY(posY)  {}
                ~Weapon() = default;

                void setWeapon(double cooldDown, double xSpeed, double ySpeed, double posX, double posY) {
                    _coolDown = cooldDown;
                    _xSpeed = xSpeed;
                    _ySpeed = ySpeed;
                    _posX = posX;
                    _posY = posY;
                }
                template<class Archive>
                void serialize(Archive & ar, const unsigned int version) {
                    ar & _idComponent;
                    ar & _type;
                    ar & _coolDown;
                    ar & _xSpeed;
                    ar & _ySpeed;
                    ar & _posX;
                    ar & _posY;
                }
                virtual CONFIG::CompType getType() {return _type;};
                virtual void setType(const CONFIG::CompType type) {_type = type;};
                virtual int getId() {return _idComponent;};
                virtual void setId(const int id) {_idComponent = id;};

            protected:
                int _idComponent;
                CONFIG::CompType _type;

            private:
                double _coolDown;
                double _xSpeed;
                double _ySpeed;
                double _posX;
                double _posY;
        };
    }