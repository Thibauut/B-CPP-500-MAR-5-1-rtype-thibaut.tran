/*
** EPITECH PROJECT, 2023
** Health
** File description:
** Health
*/

#pragma once

#include "../../Components/AComponent/AComponent.hpp"

namespace GameEngine {
    class Health : public AComponent {
        public:
            friend class boost::serialization::access;
            friend class AComponent;
            Health() : AComponent() {}
            Health(CONFIG::CompType type, int id, int value) : AComponent(CONFIG::CompType::HEALTH), _idComponent(id), _type(type), _hp(value)
            {}
            ~Health() = default;

            bool decrementHealth(int damage) {
                if (_hp <= 0)
                    return false;
                _hp -= damage;
                return true;
            }

            void setHealth(int hp) {
                _hp = hp;
            }

            int getHealth() const {
                return _hp;
            }
            template<class Archive>
            void serialize(Archive & ar, const unsigned int version) {
                ar.template register_type<Health>();
                ar & boost::serialization::base_object<AComponent>(*this);
                ar & _idComponent;
                ar & _type;
                ar & _hp;
            }
            virtual CONFIG::CompType getType() {return _type;};
            virtual void setType(const CONFIG::CompType type) {_type = type;};
            virtual int getId() {return _idComponent;};
            virtual void setId(const int id) {_idComponent = id;};

        protected:
            int _idComponent;
            CONFIG::CompType _type;

        private:
            int _hp;
    };
}

BOOST_CLASS_EXPORT_KEY(GameEngine::Health);
