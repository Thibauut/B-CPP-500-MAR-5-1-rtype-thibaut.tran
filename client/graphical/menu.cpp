/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** menu.cpp
*/

#include "../include/menu.hpp"

Menu::Menu()
{

    _window = new sf::RenderWindow (sf::VideoMode(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT), sf::String(MENU_TITLE));
    _inGame = false;
    _font.loadFromFile("assets/fonts/WANTONE.otf");

    // PARALLAX
    sfmlFunc.LoadSprite(_background, _backgroundTexture, "assets/images/background_1.png", 0, 0, 7, 7);
    sf::IntRect rectBackground(0, 0, 256, 224);
    _rectBackground = rectBackground;
    _background.setTextureRect(_rectBackground);

    sfmlFunc.LoadSprite(_background2, _backgroundTexture2, "assets/images/background_2.png", 0, 0, 7, 7);
    sf::IntRect rectBackground2(0, 0, 256, 224);
    _rectBackground2 = rectBackground2;
    _background2.setTextureRect(_rectBackground2);

    // TITLE
    sfmlFunc.LoadSprite(_title, _titleTexture, "assets/images/title.png", -70, 0, 1, 1);

    // TEXT FIELDS
    sfmlFunc.CreateTextField(_textField, _text_name, _font, "Enter your name", sf::Vector2f(600, 40), sf::Vector2f(590, 500));
    sfmlFunc.CreateTextField(_textField2, _text_ip, _font, "Server IP", sf::Vector2f(600, 40), sf::Vector2f(590, 600));
    sfmlFunc.CreateTextField(_textField3, _text_port, _font, "Server Port", sf::Vector2f(600, 40), sf::Vector2f(590, 700));

    // INPUT TEXT
    sfmlFunc.createText(_text_name_input, _font, "letibz", 24, sf::Color::White, sf::Vector2f(605, 508));
    sfmlFunc.createText(_text_ip_input, _font, "127.0.0.1", 24, sf::Color::White, sf::Vector2f(605, 608));
    sfmlFunc.createText(_text_port_input, _font, "3000", 24, sf::Color::White, sf::Vector2f(605, 708));

    // BUTTONS
    sfmlFunc.CreateButton(_button, _buttonText, _font, "Connect", sf::Vector2f(200, 50), sf::Vector2f(800, 800), 45);

    sfmlFunc.CreateButton(_buttonCreate, _buttonCreateText, _font, "Create", sf::Vector2f(200, 50), sf::Vector2f(1200, 800), 57);
    sfmlFunc.CreateButton(_buttonDisconnect, _buttonDisconnectText, _font, "Disconnect", sf::Vector2f(200, 50), sf::Vector2f(400, 800), 25);
    sfmlFunc.CreateButton(_buttonDelete, _buttonDeleteText, _font, "Delete", sf::Vector2f(200, 50), sf::Vector2f(800, 800), 57);

    sfmlFunc.CreateButton(_buttonLeave, _buttonLeaveText, _font, "Leave", sf::Vector2f(200, 50), sf::Vector2f(620, 800), 57);
    sfmlFunc.CreateButton(_buttonReady, _buttonReadyText, _font, "Ready", sf::Vector2f(200, 50), sf::Vector2f(980, 800), 57);

    // ROOM
    _roomMenu.setSize(sf::Vector2f(1000, 310));
    _roomMenu.setFillColor(sf::Color::Black);
    _roomMenu.setOutlineColor(sf::Color::White);
    _roomMenu.setOutlineThickness(5.0f);
    _roomMenu.setPosition(sf::Vector2f(400, 460));


}

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

void Menu::Loop()
{
    while (_window->isOpen()) {
        if (!_inGame) {
            HandleEvents();
            AnimateBackground();
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

        if (_event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mousePos = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window));
            sf::FloatRect textBounds = _textField.getGlobalBounds();
            sf::FloatRect textBounds2 = _textField2.getGlobalBounds();
            sf::FloatRect textBounds3 = _textField3.getGlobalBounds();
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
        }

        if (_isFocused && _event.type == sf::Event::TextEntered && _current_input == 0) {
            if (_event.text.unicode == 8 && !_inputName.empty()) {
                _inputName.pop_back();
                _text_name_input.setString(_inputName);
            } else if (_event.text.unicode >= 32 && _event.text.unicode < 127 && _inputName.size() < 10) {
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

        // anim button
        if (_event.type == sf::Event::MouseMoved) {
            sf::Vector2f mousePos = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window));
            sf::FloatRect buttonBounds = _button.getGlobalBounds();

            sf::FloatRect buttonCreateBounds = _buttonCreate.getGlobalBounds();
            sf::FloatRect buttonDisconnectBounds = _buttonDisconnect.getGlobalBounds();
            sf::FloatRect buttonDeleteBounds = _buttonDelete.getGlobalBounds();
            sf::FloatRect buttonLeaveBounds = _buttonLeave.getGlobalBounds();
            sf::FloatRect buttonReadyBounds = _buttonReady.getGlobalBounds();

            sfmlFunc.HandleButtonHover(_button, _buttonText, isButtonHovered, mousePos, buttonBounds);
            sfmlFunc.HandleButtonHover(_buttonCreate, _buttonCreateText, isButtonHovered, mousePos, buttonCreateBounds);
            sfmlFunc.HandleButtonHover(_buttonDisconnect, _buttonDisconnectText, isButtonHovered, mousePos, buttonDisconnectBounds);
            sfmlFunc.HandleButtonHover(_buttonDelete, _buttonDeleteText, isButtonHovered, mousePos, buttonDeleteBounds);
            sfmlFunc.HandleButtonHover(_buttonLeave, _buttonLeaveText, isButtonHovered, mousePos, buttonLeaveBounds);
            sfmlFunc.HandleButtonHover(_buttonReady, _buttonReadyText, isButtonHovered, mousePos, buttonReadyBounds);
        }

        if (_event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mousePos = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window));
            sf::FloatRect buttonBounds = _button.getGlobalBounds();

            sf::FloatRect buttonCreateBounds = _buttonCreate.getGlobalBounds();
            sf::FloatRect buttonDisconnectBounds = _buttonDisconnect.getGlobalBounds();
            sf::FloatRect buttonDeleteBounds = _buttonDelete.getGlobalBounds();
            sf::FloatRect buttonLeaveBounds = _buttonLeave.getGlobalBounds();
            if (buttonBounds.contains(mousePos)) {
                //client connection sending
                _isConnected = true;
                std::cout << "Connect" << std::endl;
            }
            if (buttonDisconnectBounds.contains(mousePos)) {
                //client disconnection sending
                _isConnected = false;
                std::cout << "Disconnect" << std::endl;
            }
            if (buttonCreateBounds.contains(mousePos) && _roomList.size() < 6) {
                //client room creaction sending
                std::cout << "Create" << std::endl;

                Room *room = new Room();
                sfmlFunc.CreateButton(room->room, room->roomText, _font, ("Room " + std::to_string(_roomIndex)), sf::Vector2f(1000, 40), sf::Vector2f(400, 460 + (_roomSizeIndex * _roomList.size())), 150);
                room->nbPlayers.setFont(_font);
                room->nbPlayers.setString("0/4"); // server response
                room->nbPlayers.setCharacterSize(24);
                room->nbPlayers.setFillColor(sf::Color::White);
                room->nbPlayers.setPosition(sf::Vector2f(400, 460 + (_roomSizeIndex * _roomList.size())) + sf::Vector2f(40, 10));

                _roomList.push_back(room);
                _roomIndex++;
            }

            if (!_roomList.empty()) {
                for (auto &room : _roomList) {
                    if (room->room.getGlobalBounds().contains(mousePos)) {
                        std::cout << "Clicked: " << room->roomText.getString().toAnsiString() << std::endl;
                        _selectedRoom = room;
                    }
                }
            }

            if (buttonDeleteBounds.contains(mousePos)) {
                //client room deletion sending
                std::cout << "Delete" << std::endl;
                if (!_roomList.empty()) {
                    delete _roomList.back();
                    _roomList.pop_back();
                    _roomIndex--;
                }
            }

            if (buttonLeaveBounds.contains(mousePos)) {
                std::cout << "Leave" << std::endl;
                _selectedRoom = nullptr;
            }

        }
    }
}

void Menu::Draw() {
    _window->clear(sf::Color::Black);

    _window->draw(_background);
    _window->draw(_background2);
    _window->draw(_title);

    if (!_isConnected) {
        _window->draw(_textField);
        _window->draw(_text_name);
        _window->draw(_text_name_input);

        _window->draw(_textField2);
        _window->draw(_text_ip);
        _window->draw(_text_ip_input);

        _window->draw(_textField3);
        _window->draw(_text_port);
        _window->draw(_text_port_input);

        _window->draw(_button);
        _window->draw(_buttonText);
    }
    if (_isConnected && !_selectedRoom) {
        _window->draw(_roomMenu);
        _window->draw(_buttonCreate);
        _window->draw(_buttonCreateText);
        _window->draw(_buttonDisconnect);
        _window->draw(_buttonDisconnectText);
        _window->draw(_buttonDelete);
        _window->draw(_buttonDeleteText);
        for (auto &room : _roomList) {
            _window->draw(room->room);
            _window->draw(room->roomText);
            _window->draw(room->nbPlayers);

        }

    }
    if (_isConnected && _selectedRoom) {
        _window->draw(_roomMenu);
        _window->draw(_buttonLeave);
        _window->draw(_buttonLeaveText);
        _window->draw(_buttonReady);
        _window->draw(_buttonReadyText);
    }

    _window->display();
}