/*
** EPITECH PROJECT, 2023
** aa
** File description:
** sfml_func.hpp
*/

#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <functional>

class SfmlFunc {
    public:
        SfmlFunc();
        sf::Sprite CreateSprite(std::string path, float posX, float posY, float scaleX, float scaleY);
};