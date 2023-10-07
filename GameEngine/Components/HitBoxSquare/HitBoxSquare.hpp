/*
** EPITECH PROJECT, 2023
** HitBoxSquare
** File description:
** HitBoxSquare
*/
#pragma once
#include "../AComponent/AComponent.hpp"

namespace GameEngine {

    class HitBoxSquare : public IComponent {
        public:
            HitBoxSquare(CONFIG::CompType type, int id, int x, int y) : _idComponent(id), _type(type), _x(x), _y(y) {}
            ~HitBoxSquare() = default;

            void setHitbox(int x, int y){ _x = x, _y = y;}


            int getHitBoxSquareX()
            {
                return _x;
            }

            int getHitBoxSquareY()
            {
                return _y;
            }

            std::pair<int, int> getHitBoxSquare()
            {
                return std::make_pair(_x, _y);
            }
            template<class Archive>
            void serialize(Archive & ar, const unsigned int version) {
                ar & _idComponent;
                ar & _type;
                ar & _x;
                ar & _y;
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