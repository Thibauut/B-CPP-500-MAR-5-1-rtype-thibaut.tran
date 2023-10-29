/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** init.cpp
*/

#include "../../include/menu.hpp"

void Menu::Init() {
    videoMode.width = 1920;
    videoMode.height = 1080;
    _window = new sf::RenderWindow(videoMode, "R-TYPE",sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
    _inGame = false;
    _font.loadFromFile("assets/fonts/WANTONE.otf");
    sfmlFunc.LoadSprite(_title, _titleTexture, "assets/images/title.png", 0, 0, 1, 1);
}

void Menu::InitBackground() {
    sfmlFunc.LoadSprite(_background, _backgroundTexture, "assets/images/background_1.png", 0, 0, 8, 8);
    sf::IntRect rectBackground(0, 0, 256, 224);
    _rectBackground = rectBackground;
    _background.setTextureRect(_rectBackground);

    sfmlFunc.LoadSprite(_background2, _backgroundTexture2, "assets/images/background_2.png", 0, 0, 8, 8);
    sf::IntRect rectBackground2(0, 0, 256, 224);
    _rectBackground2 = rectBackground2;
    _background2.setTextureRect(_rectBackground2);
}

void Menu::InitSprites() {
    sfmlFunc.LoadSprite(_next_level_choose, _next_level_choose_texture, "assets/images/plus.png", 1370, 697, 0.1, 0.1);
    sfmlFunc.LoadSprite(_previous_level_choose, _previous_level_choose_texture, "assets/images/moins.png", 530, 697, 0.1, 0.1);

    sfmlFunc.LoadSprite(_next_GameType_choose, _next_GameType_choose_texture, "assets/images/plus.png", 1370, 737, 0.1, 0.1);
    sfmlFunc.LoadSprite(_previous_GameType_choose, _previous_GameType_choose_texture, "assets/images/moins.png", 530, 737, 0.1, 0.1);

    sfmlFunc.LoadSprite(_addSlot, _addSlotTexture, "assets/images/plus.png", 1370, 607, 0.1, 0.1);
    sfmlFunc.LoadSprite(_removeSlot, _removeSlotTexture, "assets/images/moins.png", 530, 607, 0.1, 0.1);
    sfmlFunc.LoadSprite(_roomDelete, _roomDeleteTexture, "assets/images/delete.png", 1660, 810, 0.2, 0.2);
}

void Menu::InitText() {
    sfmlFunc.CreateTextField(_textField, _text_name, _font, "Your name", sf::Vector2f(650, 40), sf::Vector2f(640, 500));
    sfmlFunc.CreateTextField(_textField2, _text_ip, _font, "Server IP", sf::Vector2f(650, 40), sf::Vector2f(640, 600));
    sfmlFunc.CreateTextField(_textField3, _text_port, _font, "Server Port", sf::Vector2f(650, 40), sf::Vector2f(640, 700));

    sfmlFunc.CreateTextField(_textField_room, _text_name_room, _font, "Room name", sf::Vector2f(650, 40), sf::Vector2f(640, 500));
    sfmlFunc.CreateTextField(_textField2_room, _text_slot_room, _font, "Slot number", sf::Vector2f(650, 40), sf::Vector2f(640, 600));

    sfmlFunc.createText(_text_name_input, _font, "Username", 24, sf::Color::White, sf::Vector2f(655, 508));
    sfmlFunc.createText(_text_ip_input, _font, _inputIp, 24, sf::Color::White, sf::Vector2f(655, 608));
    sfmlFunc.createText(_text_port_input, _font, _inputPort, 24, sf::Color::White, sf::Vector2f(655, 708));
    sfmlFunc.createText(_text_ip_input, _font, _inputIp, 24, sf::Color::White, sf::Vector2f(655, 608));

    sfmlFunc.createText(_text_level_choose, _font, "None", 24, sf::Color::White, sf::Vector2f(880, 697));
    sfmlFunc.createText(_text_GameType_choose, _font, "Normal", 24, sf::Color::White, sf::Vector2f(880, 737));

    sfmlFunc.createText(_text_name_input_room, _font, "Room 1", 24, sf::Color::White, sf::Vector2f(655, 508));
    sfmlFunc.createText(_text_slot_input_room, _font, "0", 24, sf::Color::White, sf::Vector2f(655, 608));
}

void Menu::InitButton() {
    sfmlFunc.CreateButton(_button, _buttonText, _font, "Connect", sf::Vector2f(200, 50), sf::Vector2f(860, 800), 45);

    sfmlFunc.CreateButton(_buttonCreate, _buttonCreateText, _font, "Create", sf::Vector2f(200, 50), sf::Vector2f(1210, 800), 57);
    sfmlFunc.CreateButton(_buttonDisconnect, _buttonDisconnectText, _font, "Disconnect", sf::Vector2f(200, 50), sf::Vector2f(510, 800), 25);

    sfmlFunc.CreateButton(_buttonLeave, _buttonLeaveText, _font, "Leave", sf::Vector2f(200, 50), sf::Vector2f(1210, 800), 57);
    sfmlFunc.CreateButton(_buttonReady, _buttonReadyText, _font, "Ready", sf::Vector2f(200, 50), sf::Vector2f(510, 800), 57);

// -------------------------------------------------------

// Creer les boutons pour choisir le type de jeu mzee


// -------------------------------------------------------
    sfmlFunc.CreateButton(_buttonCreateRoom, _buttonCreateRoomText, _font, "Create", sf::Vector2f(200, 50), sf::Vector2f(730, 800), 57);
    sfmlFunc.CreateButton(_buttonCancel, _buttonCancelText, _font, "Cancel", sf::Vector2f(200, 50), sf::Vector2f(990, 800), 57);
}

void Menu::InitCreateRoom() {
    _roomMenu.setSize(sf::Vector2f(1000, 310));
    _roomMenu.setFillColor(sf::Color::Black);
    _roomMenu.setOutlineColor(sf::Color::White);
    _roomMenu.setOutlineThickness(5.0f);
    _roomMenu.setPosition(sf::Vector2f(460, 460));
}
