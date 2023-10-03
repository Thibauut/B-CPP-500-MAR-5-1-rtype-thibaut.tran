/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** handle_events.cpp
*/

#include "../../include/menu.hpp"

void Menu::HandleEventsFocus() {
    if (_event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window));
        sf::FloatRect textBounds = _textField.getGlobalBounds();
        sf::FloatRect textBounds2 = _textField2.getGlobalBounds();
        sf::FloatRect textBounds3 = _textField3.getGlobalBounds();
        sf::FloatRect textBounds_room = _textField_room.getGlobalBounds();
        sf::FloatRect textBounds2_room = _textField2_room.getGlobalBounds();

        if (textBounds.contains(mousePos)) {
            _isFocused = true;
            _current_input = 0;
            _textField.setOutlineColor(sf::Color(178, 102, 255));
        } else {
            _isFocused = false;
            _textField.setOutlineColor(sf::Color::White);
        }
        if (textBounds2.contains(mousePos)) {
            _isFocused2 = true;
            _current_input = 1;
            _textField2.setOutlineColor(sf::Color(178, 102, 255));
        } else {
            _isFocused2 = false;
            _textField2.setOutlineColor(sf::Color::White);
        }
        if (textBounds3.contains(mousePos)) {
            _isFocused3 = true;
            _current_input = 2;
            _textField3.setOutlineColor(sf::Color(178, 102, 255));
        } else {
            _isFocused3 = false;
            _textField3.setOutlineColor(sf::Color::White);
        }
        if (textBounds_room.contains(mousePos) && _isCreatingRoom) {
            _isFocused_room = true;
            _current_input = 3;
            _textField_room.setOutlineColor(sf::Color(178, 102, 255));
        } else {
            _isFocused_room = false;
            _textField_room.setOutlineColor(sf::Color::White);
        }
    }
}

void Menu::HandleEventText() {
    if (_isFocused && _event.type == sf::Event::TextEntered && _current_input == 0) {
        if (_event.text.unicode == 8 && !_inputName.empty()) {
            _inputName.pop_back();
            _text_name_input.setString(_inputName);
        } else if (_event.text.unicode >= 32 && _event.text.unicode < 127 && _inputName.size() < 20) {
            _inputName += static_cast<char>(_event.text.unicode);
            _text_name_input.setString(_inputName);
        }
    }

    if (_isFocused2 && _event.type == sf::Event::TextEntered && _current_input == 1) {
        if (_event.text.unicode == 8 && !_inputIp.empty()) {
            _inputIp.pop_back();
            _text_ip_input.setString(_inputIp);
        } else if (_event.text.unicode >= 32 && _event.text.unicode < 127 && _inputIp.size() < 15) {
            _inputIp += static_cast<char>(_event.text.unicode);
            _text_ip_input.setString(_inputIp);
        }
    }

    if (_isFocused3 && _event.type == sf::Event::TextEntered && _current_input == 2) {
        if (_event.text.unicode == 8 && !_inputPort.empty()) {
            _inputPort.pop_back();
            _text_port_input.setString(_inputPort);
        } else if (_event.text.unicode >= 32 && _event.text.unicode < 127 && _inputPort.size() < 5) {
            _inputPort += static_cast<char>(_event.text.unicode);
            _text_port_input.setString(_inputPort);
        }
    }

    if (_isFocused_room && _event.type == sf::Event::TextEntered && _current_input == 3) {
        if (_event.text.unicode == 8 && !_inputName_room.empty()) {
            _inputName_room.pop_back();
            _text_name_input_room.setString(_inputName_room);
        } else if (_event.text.unicode >= 32 && _event.text.unicode < 127 && _inputName_room.size() < 20) {
            _inputName_room += static_cast<char>(_event.text.unicode);
            _text_name_input_room.setString(_inputName_room);
        }
    }
}

