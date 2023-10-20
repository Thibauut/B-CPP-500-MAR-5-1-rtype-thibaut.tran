/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** AComponent.hpp
*/

#pragma once
#include <iostream>
#include <list>
#include <memory>
#include "../../Interfaces/IComponent/IComponent.hpp"
#include <boost/serialization/unique_ptr.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/string.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace GameEngine {

    class AComponent : public IComponent{
        public:
            AComponent() {
                _id = 0;
            };
            AComponent(CONFIG::CompType type) : _type(type) {
                _id = 0;
            };
            AComponent(AComponent &component) {
                _type = component.getType();
                _id = component.getId();
                _uuid = component.getUuid();
            };
            virtual ~AComponent() = default;
            template <class Archive>

            void serialize(Archive & ar, const unsigned int version) {
                ar.template register_type<AComponent>();
                ar & _id;
                // ar & _uuid;
                ar & _type;
            }

            virtual CONFIG::CompType getType() {return _type;};
            virtual void setType(const CONFIG::CompType type) {_type = type;};
            virtual int getId() {return _id;};
            virtual void setId(const int id) {_id = id;};
            virtual std::string getUuid() {return _uuid;};

        protected:
            int _id;
            CONFIG::CompType _type;
            std::string _uuid;
    };
}
