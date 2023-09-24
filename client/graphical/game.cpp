/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** game.cpp
*/

#include "../include/game.hpp"

Game::Game(sf::RenderWindow *window): _window(window)
{
    _font.loadFromFile("assets/fonts/WANTONE.otf");

}

void Game::Loop()
{
    while (_window->isOpen()) {
        HandleEvents();
        Draw();
    }
}

void Game::HandleEvents()
{
    while (_window->pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            _window->close();


    }
}

void Game::Draw()
{
        _window->clear(sf::Color::Black);

        _window->display();
}