/*
** EPITECH PROJECT, 2023
** HitBoxCircle
** File description:
** HitBoxCircle
*/
#pragma once
#include "../AComponent/AComponent.hpp"

namespace GameEngine {

    class HitBoxCircle : public IComponent {
        public:
            HitBoxCircle(CONFIG::CompType type, int id, int radius) : _idComponent(id), _type(type), _radius(radius) {}
            ~HitBoxCircle() = default;

            void setHitBoxCircleRadius(int radius){ _radius = radius;}


            int getHitBoxCircleRadius()
            {
                return _radius;
            }
            template<class Archive>
            void serialize(Archive & ar, const unsigned int version) {
                ar & _idComponent;
                ar & _type;
                ar & _radius;
            }
            virtual CONFIG::CompType getType() {return _type;};
            virtual void setType(const CONFIG::CompType type) {_type = type;};
            virtual int getId() {return _idComponent;};
            virtual void setId(const int id) {_idComponent = id;};

        protected:
            int _idComponent;
            CONFIG::CompType _type;

        private:
            int _radius;
    };
}