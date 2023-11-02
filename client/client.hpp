/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Client.hpp
*/

#pragma once

#include "network/OpenUDP/OpenUDP.cpp"
#include "../GameEngine/Components/Menu/Menu.hpp"
#include "../GameEngine/Systems/SysRender/SysRender.hpp"
#include "../GameEngine/GameEngine.hpp"

class Client {
    public:
        Client(): gameEngine_(*std::make_shared<EntityManager>()) {};
        ~Client() = default;

        GameEngine::Engine gameEngine_;
};
