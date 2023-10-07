/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** IComponent.hpp
*/

#pragma once
#include "../../Utils/Utils.hpp"
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/export.hpp>

namespace GameEngine {

    class IComponent {
        public:

            using Ptr = std::unique_ptr<IComponent>;

            virtual ~IComponent() = default;
            virtual CONFIG::CompType getType() = 0;
            virtual void setType(const CONFIG::CompType type) = 0;
            virtual int getId() = 0;
            virtual void setId(const int id) = 0;
            template <typename Archive>
            void serialize(Archive& ar, const unsigned int version) {}
    };
}