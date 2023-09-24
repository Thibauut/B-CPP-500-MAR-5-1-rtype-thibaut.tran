/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** anim.cpp
*/

#include "../../include/menu.hpp"

void Menu::AnimateBackground()
{
    sf::Time elapsed = _clock.getElapsedTime();
    if (elapsed.asSeconds() > 0.03) {
        _rectBackground.left += 1;
        _rectBackground2.left += 2;
        if (_rectBackground.left >= 256) {
            _rectBackground.left = 0;
        }
        if (_rectBackground2.left >= 256) {
            _rectBackground2.left = 0;
        }
        _background.setTextureRect(_rectBackground);
        _background2.setTextureRect(_rectBackground2);
        _clock.restart();
    }
}

void Menu::AnimButtonEvents() {
    if (_event.type == sf::Event::MouseMoved) {
        sf::Vector2f mousePos = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window));
        sf::FloatRect buttonBounds = _button.getGlobalBounds();
        sf::FloatRect buttonCreateBounds = _buttonCreate.getGlobalBounds();
        sf::FloatRect buttonDisconnectBounds = _buttonDisconnect.getGlobalBounds();
        sf::FloatRect buttonLeaveBounds = _buttonLeave.getGlobalBounds();
        sf::FloatRect buttonReadyBounds = _buttonReady.getGlobalBounds();
        sf::FloatRect buttonCreateRoomBounds = _buttonCreateRoom.getGlobalBounds();
        sf::FloatRect buttonDeleteRoomBounds = _roomDelete.getGlobalBounds();
        sf::FloatRect buttonCancelRoomBounds = _buttonCancel.getGlobalBounds();

        sfmlFunc.HandleButtonHover(_button, _buttonText, isButtonHovered, mousePos, buttonBounds);
        sfmlFunc.HandleButtonHover(_buttonCreate, _buttonCreateText, isButtonHovered, mousePos, buttonCreateBounds);
        sfmlFunc.HandleButtonHover(_buttonDisconnect, _buttonDisconnectText, isButtonHovered, mousePos, buttonDisconnectBounds);
        sfmlFunc.HandleButtonHover(_buttonLeave, _buttonLeaveText, isButtonHovered, mousePos, buttonLeaveBounds);
        sfmlFunc.HandleButtonHover(_buttonReady, _buttonReadyText, isButtonHovered, mousePos, buttonReadyBounds);
        sfmlFunc.HandleButtonHover(_buttonCreateRoom, _buttonCreateRoomText, isButtonHovered, mousePos, buttonCreateRoomBounds);
        sfmlFunc.HandleSpriteHover(_roomDelete, isButtonHovered, mousePos, buttonDeleteRoomBounds);
        sfmlFunc.HandleButtonHover(_buttonCancel, _buttonCancelText, isButtonHovered, mousePos, buttonCancelRoomBounds);
    }
}
