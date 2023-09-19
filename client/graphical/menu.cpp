/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** menu.cpp
*/

#include "../include/menu.hpp"

Menu::Menu()
{
    SfmlFunc sfmlFunc;
    _window = new sf::RenderWindow (sf::VideoMode(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT), sf::String(MENU_TITLE));
    _inGame = false;
    _background = sfmlFunc.CreateSprite("assets/background.png", 0, 0, 1, 1);

}

void Menu::Loop()
{
    while (_window->isOpen()) {
        if (!_inGame) {
            HandleEvents();
            Draw();
        } else {
            //run game
        }
    }
}

void Menu::HandleEvents() {
    while (_window->pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            _window->close();
    }
}

void Menu::Draw() {
    _window->clear(sf::Color::Black);



    _window->display();
}