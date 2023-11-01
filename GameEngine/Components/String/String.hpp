/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** String.hpp
*/

#pragma once

#include "../AComponent/AComponent.hpp"
#include <SFML/Graphics.hpp>
#include <string>

namespace GameEngine {

    class String : public AComponent {
        public:
            friend class boost::serialization::access;
            friend class AComponent;
            String() : AComponent() {};
            String(std::string string)
            : AComponent(CONFIG::CompType::STRING), _idComponent(895), _type(CONFIG::CompType::STRING) {
                _string = string;
            }

            String(String const &string) : AComponent() {
                _idComponent = string._idComponent;
                _type = CONFIG::CompType::STRING;
            }

            ~String() = default;

            std::string getString() {return _string;};

            void setString(std::string &string) {_string = string;};

            template<class Archive>
            void serialize(Archive & ar, const unsigned int version) {
                ar.template register_type<Sprite>();
                ar & boost::serialization::base_object<AComponent>(*this);
                ar & _idComponent;
                ar & _type;
                ar & _string;
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
            std::string _string;
    };
}

BOOST_CLASS_EXPORT_KEY(GameEngine::String);
