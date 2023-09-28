/*
** EPITECH PROJECT, 2023
** Strenght
** File description:
** Strenght
*/

#pragma once
#include "../AComponent/AComponent.hpp"

namespace GameEngine {

    template <class T>
    class Strenght : public AComponent {
        public:
            Strenght() {}
            ~Strenght() = default;

           void setComponent() {
                std::cout << "Component : {render.set}" << std::endl;
            }

            virtual CONFIG::CompType getType() {return _type;};
            virtual void setType(const CONFIG::CompType type) {_type = type;};
            virtual int getId() {return _id;};
            virtual void setId(const int id) {return id};

        protected:
            int _idComponent;
            CONFIG::CompType _type;

        private:
            int _damage;
    };
}
