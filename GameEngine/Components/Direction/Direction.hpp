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
            Direction() : AComponent() {
                _idComponent = 0;
                _type = CONFIG::CompType::DIRECTION;
                _direction = 1;
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
            }
            Direction(CONFIG::CompType type, int id) : AComponent(CONFIG::CompType::DIRECTION), _idComponent(id), _type(type), _direction(1) {
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
            }
            Direction(CONFIG::CompType type, int id, int value) : AComponent(CONFIG::CompType::DIRECTION), _idComponent(id), _type(type), _direction(value) {
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
            }
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
                // ar & _uuid;
                ar & _idComponent;
                ar & _type;
                ar & _direction;
            }
            virtual CONFIG::CompType getType() {return _type;};
            virtual void setType(const CONFIG::CompType type) {_type = type;};
            virtual int getId() {return _idComponent;};
            virtual void setId(const int id) {_idComponent = id;};
            virtual std::string getUuid() {return _uuid;};

        protected:
            int _idComponent;
            CONFIG::CompType _type;
            std::string _uuid;

        private:
            int _direction;
    };
}

BOOST_CLASS_EXPORT_KEY(GameEngine::Direction);
