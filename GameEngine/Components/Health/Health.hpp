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
            Health() : AComponent() {
                _idComponent = 0;
                _type = CONFIG::CompType::HEALTH;
                _hp = 1;
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
            }
            Health(CONFIG::CompType type, int id, int value) : AComponent(CONFIG::CompType::HEALTH), _idComponent(id), _type(type), _hp(value) {
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
            }

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
                // ar & _uuid;
                ar & _idComponent;
                ar & _type;
                ar & _hp;
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
            int _hp;
    };
}

BOOST_CLASS_EXPORT_KEY(GameEngine::Health);
