/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** game.hpp
*/

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
#include "../graphical/utils/sfml_func.cpp"

#define DEFAULT_WINDOW_WIDTH 1920
#define DEFAULT_WINDOW_HEIGHT 1080
#define GAME_TITLE  "R-Type"

#pragma once

class Game {
    public:
        Game(sf::RenderWindow *window);
        ~Game() = default;
        void Loop();
        void HandleEvents();
        void Draw();

    SfmlFunc sfmlFunc;
    sf::RenderWindow *_window;
    sf::VideoMode _videoMode;
    sf::Event _event;
    sf::Font _font;
    sf::Clock _clock;
};