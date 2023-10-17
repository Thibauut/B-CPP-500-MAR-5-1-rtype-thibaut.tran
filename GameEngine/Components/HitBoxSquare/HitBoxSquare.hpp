/*
** EPITECH PROJECT, 2023
** HitBoxSquare
** File description:
** HitBoxSquare
*/
#pragma once
#include "../AComponent/AComponent.hpp"
#include "../../Utils/Utils.hpp"

namespace GameEngine {

    class HitBoxSquare : public AComponent {
        public:
            HitBoxSquare() : AComponent(), _idComponent(0), _type(CONFIG::CompType::HITBOXSQUARE) {}
            HitBoxSquare(CONFIG::CompType type, int id)
            : AComponent(), _idComponent(id), _type(type) {
                _rectangle.width = 0;
                _rectangle.height = 0;
            }
            HitBoxSquare(CONFIG::CompType type, int id, sf::IntRect rectangle)
            : AComponent(), _idComponent(id), _type(type) {
                _rectangle.width = rectangle.width;
                _rectangle.height = rectangle.height;
            }
            ~HitBoxSquare() = default;
            int getWidth()
            {
                return _rectangle.width;
            }
            int getHeight()
            {
                return _rectangle.height;
            }

            void setHitboxSize(int width, int height)
            {
                _rectangle.width = width;
                _rectangle.height = height;
            }

            void setHitboxPosition(int x, int y)
            {
                _rectangle.left = x;
                _rectangle.top = y;
            }


            sf::IntRect getRectangle()
            {
                return _rectangle;
            }

            template<class Archive>
            void serialize(Archive & ar, const unsigned int version) {
                ar.template register_type<HitBoxSquare>();
                ar & boost::serialization::base_object<AComponent>(*this);
                ar & _idComponent;
                ar & _type;
            }
            virtual CONFIG::CompType getType() {return _type;};
            virtual void setType(const CONFIG::CompType type) {_type = type;};
            virtual int getId() {return _idComponent;};
            virtual void setId(const int id) {_idComponent = id;};

        protected:
            int _idComponent;
            CONFIG::CompType _type;

        private:
            sf::IntRect _rectangle;
    };
}
BOOST_CLASS_EXPORT_KEY(GameEngine::HitBoxSquare);