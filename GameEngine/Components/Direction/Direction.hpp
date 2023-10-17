/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Direction.hpp
*/

#pragma once

#include "../../Components/AComponent/AComponent.hpp"

namespace GameEngine {
    class Direction : public AComponent {
        public:
            friend class boost::serialization::access;
            friend class AComponent;
            Direction() : AComponent() {}
            Direction(CONFIG::CompType type, int id, int value) : AComponent(CONFIG::CompType::DIRECTION), _idComponent(id), _type(type), _direction(value) {}
            ~Direction() = default;

            void setDirection(int direction) {
                _direction = direction;
            }

            int getDirection() const {
                return _direction;
            }
            template<class Archive>
            void serialize(Archive & ar, const unsigned int version) {
                ar.template register_type<Direction>();
                ar & boost::serialization::base_object<AComponent>(*this);
                ar & _idComponent;
                ar & _type;
                ar & _direction;
            }
            virtual CONFIG::CompType getType() {return _type;};
            virtual void setType(const CONFIG::CompType type) {_type = type;};
            virtual int getId() {return _idComponent;};
            virtual void setId(const int id) {_idComponent = id;};

        protected:
            int _idComponent;
            CONFIG::CompType _type;

        private:
            int _direction;
    };
}

BOOST_CLASS_EXPORT_KEY(GameEngine::Direction);
