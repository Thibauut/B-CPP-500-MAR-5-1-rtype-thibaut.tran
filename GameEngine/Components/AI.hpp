/*
** EPITECH PROJECT, 2023
** AI
** File description:
** AI
*/

#pragma once
#include "AComponent.hpp"

namespace GameEngine {

    class AI : public GameEngine::AComponenent {
        public:
            AI() : _activate(false) {}
            ~AI() = default;
            
            void setComponent() {
                std::cout << "Component : {ai.set}" << std::endl;
            }

            void setAIActive(bool activate) {
                _activate = activate;
                std::cout << "AI setter: active = " << (_activate ? "true" : "false") << std::endl;
            }

            bool isAIactive() const {
                std::cout << "AI getter : state =" << _activate << std::endl;
                return _activate;
            }
  

        private:
            bool _activate;
    };
}