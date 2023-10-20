/*
** EPITECH PROJECT, 2023
** Velocity
** File description:
** Velocity
*/

#pragma once
#include "../AComponent/AComponent.hpp"

namespace GameEngine {
    class Velocity : public AComponent {
        public:
            friend class boost::serialization::access;
            friend class AComponent;
            Velocity() : AComponent() {
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
            };
            Velocity(CONFIG::CompType type, int id, int speedMult) : _idComponent(id), _type(type), _speedMult(speedMult) {
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
            }
            ~Velocity() = default;

           void setVelocity(int speedMult) {
                _speedMult = speedMult;
            }

            int getVelocity() {
                return _speedMult;
            }

            template<class Archive>
            void serialize(Archive & ar, const unsigned int version) {
                ar.template register_type<Velocity>();
                ar & boost::serialization::base_object<AComponent>(*this);
                ar & _idComponent;
                // ar & _uuid;
                ar & _type;
                ar & _speedMult;
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
            int _speedMult;
    };
}

BOOST_CLASS_EXPORT_KEY(GameEngine::Velocity);
