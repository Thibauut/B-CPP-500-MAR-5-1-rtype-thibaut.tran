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
#include <boost/archive/binary_iarchive.hpp>
#include "../../Interfaces/IComponent/IComponent.hpp"
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/unique_ptr.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/export.hpp>

namespace GameEngine {

    class AComponent : public IComponent{
        public:
            AComponent() {};
            AComponent(CONFIG::CompType type) : _type(type) {};
            AComponent(AComponent &component) {
                _type = component.getType();
                _id = component.getId();
            };
            virtual ~AComponent() = default;
            template <class Archive>

            void serialize(Archive & ar, const unsigned int version) {
                ar.template register_type<AComponent>();
                ar & _id;
                ar & _type;
            }

            virtual CONFIG::CompType getType() {return _type;};
            virtual void setType(const CONFIG::CompType type) {_type = type;};
            virtual int getId() {return _id;};
            virtual void setId(const int id) {_id = id;};

        protected:
            int _id;
            CONFIG::CompType _type;
    };
}
