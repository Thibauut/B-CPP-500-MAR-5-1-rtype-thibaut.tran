/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** AGame.hpp
*/


#pragma once
#include "IGame.hpp"

class AGame : public IGame {
    public:
        AGame() : gameEngine_(*std::make_shared<EntityManager>()) {};
        ~AGame() {} ;

        virtual void InitBackground() {};
        virtual void AnimateBackground() {};
        virtual void Loop() {};
        virtual void HandleEvents() {};
        virtual void Draw() {};

        sf::RenderWindow *_window;
        std::shared_ptr<Entity> my_player;
        GameEngine::Engine gameEngine_;
        std::string my_id_;
        std::string portUDP_;
        std::shared_ptr<ClientOpenUDP> _clientOpenUDP;
};
