/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Bool.hpp
*/

#pragma once

/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** String.hpp
*/

#pragma once

#include "../AComponent/AComponent.hpp"
#include <string>

namespace GameEngine {

    class Bool : public AComponent {
        public:
            friend class boost::serialization::access;
            friend class AComponent;
            Bool() : AComponent() {};
            Bool(bool value)
            : AComponent(CONFIG::CompType::STRING), _idComponent(8453), _type(CONFIG::CompType::STRING) {
                _value = value;
            }

            Bool(Bool const &string) : AComponent() {
                _idComponent = string._idComponent;
                _type = CONFIG::CompType::STRING;
            }

            ~Bool() = default;

            bool getValue() {return _value;};

            void setBool(bool value) {_value = value;};

            template<class Archive>
            void serialize(Archive & ar, const unsigned int version) {
                ar.template register_type<Sprite>();
                ar & boost::serialization::base_object<AComponent>(*this);
                ar & _idComponent;
                ar & _type;
                ar & _value;
            }

            virtual CONFIG::CompType getType() {return _type;};
            virtual void setType(const CONFIG::CompType type) {_type = type;};
            virtual int getId() {return _idComponent;};
            virtual void setId(const int id) { _idComponent = id;};

        protected:
            int _idComponent;
            CONFIG::CompType _type;
            boost::uuids::uuid _uuid;

        private:
            bool _value;
    };
}

BOOST_CLASS_EXPORT_KEY(GameEngine::Bool);
