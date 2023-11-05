/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Path.hpp
*/

#pragma once

#include "../AComponent/AComponent.hpp"
#include <SFML/Graphics.hpp>
#include <string>

namespace GameEngine {

    class Path : public AComponent {
        public:
            friend class boost::serialization::access;
            friend class AComponent;
            Path() : AComponent() {};
            Path(std::string string)
            : AComponent(CONFIG::CompType::PATH), _idComponent(895), _type(CONFIG::CompType::PATH) {
                _string = string;
            }

            Path(Path const &string) : AComponent() {
                _idComponent = string._idComponent;
                _type = CONFIG::CompType::PATH;
            }

            ~Path() = default;

            std::string getPath() {return _string;};
            void setValue(const std::string string) {_string = string;};
            void setPath(std::string &string) { _string = string; };

            template<class Archive>
            void serialize(Archive & ar, const unsigned int version) {
                ar.template register_type<Path>();
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

BOOST_CLASS_EXPORT_KEY(GameEngine::Path);
