/*
** EPITECH PROJECT, 2023
** Velocity
** File description:
** Velocity
*/

#pragma once
#include "../AComponent/AComponent.hpp"

namespace GameEngine {

    class Velocity : public IComponent {
        public:
            Velocity(CONFIG::CompType type, int id, int speedMult) : _idComponent(id), _type(type), _speedMult(speedMult) {}
            ~Velocity() = default;

           void setVelocity(int speedMult) {
                _speedMult = speedMult;
            }

            int getVelocity() {
                return _speedMult;
            }
            template<class Archive>
            void serialize(Archive & ar, const unsigned int version) {
                ar & _idComponent;
                ar & _type;
                ar & _speedMult;
            }
            virtual CONFIG::CompType getType() {return _type;};
            virtual void setType(const CONFIG::CompType type) {_type = type;};
            virtual int getId() {return _idComponent;};
            virtual void setId(const int id) {_idComponent = id;};

        protected:
            int _idComponent;
            CONFIG::CompType _type;

        private:
            int _speedMult;
    };
}
