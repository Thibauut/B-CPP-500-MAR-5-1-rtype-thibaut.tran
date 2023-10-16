/*
** EPITECH PROJECT, 2023
** HitBoxCircle
** File description:
** HitBoxCircle
*/
#pragma once
#include "../AComponent/AComponent.hpp"
#include "../../Utils/Utils.hpp"

namespace GameEngine {

    class HitBoxCircle : public AComponent {
        public:
            friend class boost::serialization::access;
            friend class AComponent;
            HitBoxCircle() : AComponent(), _idComponent(0), _type(CONFIG::CompType::HITBOXSQUARE), _radius(20) {}
            HitBoxCircle(CONFIG::CompType type, int id, int radius) : AComponent(), _idComponent(id), _type(type), _radius(radius) {}
            ~HitBoxCircle() = default;

            void setHitBoxCircleRadius(int radius){ _radius = radius; _hitBox.setRadius(radius); _hitBox.setFillColor(sf::Color::Green);  }


            int getHitBoxCircleRadius()
            {
                return _radius;
            }
            template<class Archive>
            void serialize(Archive & ar, const unsigned int version) {
                ar.template register_type<HitBoxCircle>();
                ar & boost::serialization::base_object<AComponent>(*this);
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
            sf::CircleShape _hitBox;
            int _radius;
    };
}

BOOST_CLASS_EXPORT_KEY(GameEngine::HitBoxCircle);