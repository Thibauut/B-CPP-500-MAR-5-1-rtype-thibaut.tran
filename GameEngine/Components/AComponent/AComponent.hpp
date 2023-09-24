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
    template <class T>
    class AComponenent : public IComponent{
        public:
            virtual ~AComponenent() = default;

            virtual void update() = 0;

            virtual void setComponent() = 0;
            virtual void getComponent<T>() = 0;
            // virtual const int getId() = 0;

        protected:
            int _id;
    };
}
