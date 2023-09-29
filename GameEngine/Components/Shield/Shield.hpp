/*
** EPITECH PROJECT, 2023
** Strenght
** File description:
** Shield
*/
#pragma once
#include "../AComponent/AComponent.hpp"

namespace GameEngine {

    template <class T>
    class Shield : public AComponent {
        public:
            Shield(CONFIG::CompType type, int id, int max_shield_point) { _type (type), _id(id), (max_shield_point), _shield_point(max_shield_point);}
            ~Shield() = default;
            void setMaxShield(int new_max){ _max_shield_point = new_max;}
            std::pair getShieldPoint() {return _shield_point;}
            void decreaseShieldPoint(int point)
            {
                if ( _shield_point - point >= 0)
                    _shield_point -= point;
                else
                    _shield_point = 0;
            }
            void rechargeShieldToMax(){_shield_point = _max_shield_point;}
            void rechargeShield(int point)
            {
                _shield_point += point;
                if (_shield_point > _max_shield_point)
                    _shield_point = _max_shield_point;
            }


            virtual CONFIG::CompType getType() {return _type;};
            virtual void setType(const CONFIG::CompType type) {_type = type;};
            virtual int getId() {return _id;};
            virtual void setId(const int id) {return id;};

        protected:
            int _idComponent;
            CONFIG::CompType _type;

        private:
            int _max_shield_point;
            int _shield_point;
    };
}