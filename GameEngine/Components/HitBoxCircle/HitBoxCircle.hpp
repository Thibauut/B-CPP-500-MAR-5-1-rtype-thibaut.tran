/*
** EPITECH PROJECT, 2023
** HitBoxCircle
** File description:
** HitBoxCircle
*/
#pragma once
#include "../AComponent/AComponent.hpp"

namespace GameEngine {

    class HitboxCircle : public IComponent {
        public:
            HitboxCircle(CONFIG::CompType type, int id, int x, int y) : _idComponent(id), _type(type), _x(x), _y(y) {}
            ~HitboxCircle() = default;

            void setHitbox(int x, int y){ _x = x, _y = y;}


            int getHitBoxCircleX()
            {
                return _x;
            }

            int getHitBoxCircleY()
            {
                return _y;
            }

            std::pair<int, int> getHitBoxCircle()
            {
                return std::make_pair(_x, _y);
            }

            virtual CONFIG::CompType getType() {return _type;};
            virtual void setType(const CONFIG::CompType type) {_type = type;};
            virtual int getId() {return _idComponent;};
            virtual void setId(const int id) {_idComponent = id;};

        protected:
            int _idComponent;
            CONFIG::CompType _type;

        private:
            int _x;
            int _y;
    };
}