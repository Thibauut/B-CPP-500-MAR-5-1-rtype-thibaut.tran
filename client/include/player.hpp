/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** player.hpp
*/

#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <functional>

#pragma once

class PlayerUDP {
    public:

        PlayerUDP(int id, int x, int y) : _id(id), _x(x), _y(y) {};
        PlayerUDP() = default;
        ~PlayerUDP() = default;

        void setPlayerUDPId(int id) { _id = id; }
        void setPlayerUDPX(int x) { _x = x; }
        void setPlayerUDPY(int y) { _y = y; }

        int _id;
        int _x;
        int _y;
        sf::Sprite _sprite;
        sf::Texture _spriteTexture;
        sf::IntRect _rect;
        sf::Clock _clock;
};