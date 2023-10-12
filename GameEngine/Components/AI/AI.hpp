/*
** EPITECH PROJECT, 2023
** AI
** File description:
** AI
*/

#pragma once
#include "../AComponent/AComponent.hpp"
#include <chrono>

namespace GameEngine {

    class AI : public IComponent {
        public:
            AI(CONFIG::CompType type, CONFIG::AiType aiType, int id, std::chrono::milliseconds couldown) : _idComponent(id), _type(type), _aiType(aiType), _couldown(couldown), _activate(false) {}
            ~AI() = default;

            void setAIActive(bool activate) {
                _activate = activate;
                std::cout << "AI setter: active = " << (_activate ? "true" : "false") << std::endl;
            }

            bool isAIactive() const {
                std::cout << "AI getter : state = " << _activate << std::endl;
                return _activate;
            }

            virtual CONFIG::CompType getType() {return _type;};
            virtual void setType(const CONFIG::CompType type) {_type = type;};
            virtual int getId() {return _idComponent;};
            virtual void setId(const int id) {_idComponent = id;};
            CONFIG::AiType getAiType() {return _aiType;};
            void setAiType(const CONFIG::AiType aiType) {_aiType = aiType;};
            std::chrono::milliseconds getCouldown() {return _couldown;};

        protected:
            int _idComponent;
            CONFIG::CompType _type;
            CONFIG::AiType _aiType;
            std::chrono::milliseconds _couldown;

        private:
            bool _activate;
            // bool isAI_;
    };
}