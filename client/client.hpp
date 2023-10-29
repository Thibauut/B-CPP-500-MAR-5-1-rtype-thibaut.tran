/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Client.hpp
*/


#pragma once

#include "network/OpenUDP/OpenUDP.cpp"

class Client {
    public:
        Client(): gameEngine_(*std::make_shared<EntityManager>()) {

        };
        ~Client() {

        };

        void run();

        GameEngine::Engine gameEngine_;
};
