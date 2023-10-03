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

namespace GameEngine {

    class AComponent : public IComponent{
        public:
            AComponent(CONFIG::CompType type) : _type(type) {};
            AComponent(AComponent &component) {
                _type = component.getType();
                _id = component.getId();
            };
            ~AComponent() = default;

            virtual CONFIG::CompType getType() {return _type;};
            virtual void setType(const CONFIG::CompType type) {_type = type;};
            virtual int getId() {return _id;};
            virtual void setId(const int id) {_id = id;};

        protected:
            int _id;
            CONFIG::CompType _type;
    };
}
