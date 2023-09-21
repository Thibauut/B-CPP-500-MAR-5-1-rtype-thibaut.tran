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

namespace GameEngine {
    class AComponenent {
        public:
            virtual ~AComponenent() = default;

            virtual void update() = 0;

            virtual void setComponent() = 0;
            virtual void getComponent() = 0;
            virtual const int getId() = 0;

        protected:
            int _id;
    };
}
