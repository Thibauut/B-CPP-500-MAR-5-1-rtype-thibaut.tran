/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Render.hpp
*/

#pragma once
#include "../AComponent/AComponent.hpp"

namespace GameEngine {

    template <class T>
    class Render : public IComponent {
        public:
            Render() {}
            ~Render() = default;

            void setComponent() {
                std::cout << "Component : {render.set}" << std::endl;
            }

            virtual GameEngine::ListComp getType() {return _type;};
            virtual void setType(const GameEngine::ListComp type) {_type = type;};
            virtual int getId() {return _id;};
            virtual void setId(const int id) {return id};

        protected:
            int _idComponent;
            GameEngine::ListComp _type;

        private:
            std::string _pathTexture;
            int _width;
            int _height;
    };
}