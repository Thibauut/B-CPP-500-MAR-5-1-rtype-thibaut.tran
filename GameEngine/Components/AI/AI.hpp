/*
** EPITECH PROJECT, 2023
** AI
** File description:
** AI
*/

#pragma once
#include "../AComponent/AComponent.hpp"

namespace GameEngine {

    class AI : public IComponent {
        public:
            AI(GameEngine::ListComp type, int id) : _idComponent(id), _type(type), _activate(false) {}
            ~AI() = default;

            void setAIActive(bool activate) {
                _activate = activate;
                std::cout << "AI setter: active = " << (_activate ? "true" : "false") << std::endl;
            }

            bool isAIactive() const {
                std::cout << "AI getter : state =" << _activate << std::endl;
                return _activate;
            }

            virtual GameEngine::ListComp getType() {return _type;};
            virtual void setType(const GameEngine::ListComp type) {_type = type;};
            virtual int getId() {return _idComponent;};
            virtual void setId(const int id) {_idComponent = id;};

        protected:
            int _idComponent;
            GameEngine::ListComp _type;

        private:
            bool _activate;
            // bool isAI_;
    };
}