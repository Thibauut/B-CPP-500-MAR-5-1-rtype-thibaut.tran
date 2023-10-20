/*
** EPITECH PROJECT, 2023
** Strenght
** File description:
** Strenght
*/

#pragma once
#include "../AComponent/AComponent.hpp"
#include "../../Utils/Utils.hpp"

namespace GameEngine {

    class Damage : public AComponent {
        public:
            friend class boost::serialization::access;
            friend class AComponent;
            Damage() : AComponent(), _id(5), _type(CONFIG::CompType::DAMAGE), _damage(1){
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
            }
            Damage(CONFIG::CompType type, int id) : AComponent(), _type(type), _id(id)
            {
                _damage = 1;
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
            }
            Damage(CONFIG::CompType type, int id, int damage) : AComponent(), _type(type), _id(id)
            {
                _damage = damage;
                _uuid = boost::uuids::to_string(boost::uuids::random_generator()());
            }
            ~Damage() = default;
            void setDamage(int new_damage){ _damage = new_damage;}
            int getDamage() const {return _damage;}
            template<class Archive>
            void serialize(Archive & ar, const unsigned int version) {
                ar.template register_type<Damage>();
                ar & boost::serialization::base_object<AComponent>(*this);
                // ar & _uuid;
                ar & _id;
                ar & _type;
                ar & _damage;
            }
            virtual CONFIG::CompType getType() {return _type;}
            virtual void setType(const CONFIG::CompType type) {_type = type;}
            virtual int getId() {return _id;}
            virtual void setId(const int id) {_id = id;}
            virtual std::string getUuid() {return _uuid;}

        protected:
            int _id;
            CONFIG::CompType _type;
            std::string _uuid;

        private:
            int _damage;
    };
}
BOOST_CLASS_EXPORT_KEY(GameEngine::Damage);
