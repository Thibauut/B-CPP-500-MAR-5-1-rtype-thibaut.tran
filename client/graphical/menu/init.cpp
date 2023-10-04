/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** init.cpp
*/

#include "../../include/menu.hpp"

void Menu::Init() {
    _window = new sf::RenderWindow (sf::VideoMode(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT), sf::String(MENU_TITLE), sf::Style::Default);
    _inGame = false;
    _font.loadFromFile("assets/fonts/WANTONE.otf");
    sfmlFunc.LoadSprite(_title, _titleTexture, "assets/images/title.png", -70, 0, 1, 1);
}

void Menu::InitBackground() {
    sfmlFunc.LoadSprite(_background, _backgroundTexture, "assets/images/background_1.png", 0, 0, 7, 7);
    sf::IntRect rectBackground(0, 0, 256, 224);
    _rectBackground = rectBackground;
    _background.setTextureRect(_rectBackground);

    sfmlFunc.LoadSprite(_background2, _backgroundTexture2, "assets/images/background_2.png", 0, 0, 7, 7);
    sf::IntRect rectBackground2(0, 0, 256, 224);
    _rectBackground2 = rectBackground2;
    _background2.setTextureRect(_rectBackground2);
}

void Menu::InitSprites() {
    sfmlFunc.LoadSprite(_addSlot, _addSlotTexture, "assets/images/plus.png", 1260, 607, 0.1, 0.1);
    sfmlFunc.LoadSprite(_removeSlot, _removeSlotTexture, "assets/images/moins.png", 500, 607, 0.1, 0.1);
    sfmlFunc.LoadSprite(_roomDelete, _roomDeleteTexture, "assets/images/delete.png", 1560, 810, 0.2, 0.2);
}

void Menu::InitText() {
    sfmlFunc.CreateTextField(_textField, _text_name, _font, "Enter your name", sf::Vector2f(600, 40), sf::Vector2f(590, 500));
    sfmlFunc.CreateTextField(_textField2, _text_ip, _font, "Server IP", sf::Vector2f(600, 40), sf::Vector2f(590, 600));
    sfmlFunc.CreateTextField(_textField3, _text_port, _font, "Server Port", sf::Vector2f(600, 40), sf::Vector2f(590, 700));

    sfmlFunc.CreateTextField(_textField_room, _text_name_room, _font, "Room name", sf::Vector2f(600, 40), sf::Vector2f(590, 500));
    sfmlFunc.CreateTextField(_textField2_room, _text_slot_room, _font, "Slot number", sf::Vector2f(600, 40), sf::Vector2f(590, 600));

    sfmlFunc.createText(_text_name_input, _font, "letibz", 24, sf::Color::White, sf::Vector2f(605, 508));
    sfmlFunc.createText(_text_ip_input, _font, "172.20.10.4", 24, sf::Color::White, sf::Vector2f(605, 608));
    sfmlFunc.createText(_text_port_input, _font, "12345", 24, sf::Color::White, sf::Vector2f(605, 708));

    sfmlFunc.createText(_text_name_input_room, _font, "Room 1", 24, sf::Color::White, sf::Vector2f(605, 508));
    sfmlFunc.createText(_text_slot_input_room, _font, "0", 24, sf::Color::White, sf::Vector2f(605, 608));
}

void Menu::InitButton() {
    sfmlFunc.CreateButton(_button, _buttonText, _font, "Connect", sf::Vector2f(200, 50), sf::Vector2f(800, 800), 45);

    sfmlFunc.CreateButton(_buttonCreate, _buttonCreateText, _font, "Create", sf::Vector2f(200, 50), sf::Vector2f(1150, 800), 57);
    sfmlFunc.CreateButton(_buttonDisconnect, _buttonDisconnectText, _font, "Disconnect", sf::Vector2f(200, 50), sf::Vector2f(450, 800), 25);

    sfmlFunc.CreateButton(_buttonLeave, _buttonLeaveText, _font, "Leave", sf::Vector2f(200, 50), sf::Vector2f(1150, 800), 57);
    sfmlFunc.CreateButton(_buttonReady, _buttonReadyText, _font, "Ready", sf::Vector2f(200, 50), sf::Vector2f(450, 800), 57);

    sfmlFunc.CreateButton(_buttonCreateRoom, _buttonCreateRoomText, _font, "Create", sf::Vector2f(200, 50), sf::Vector2f(670, 800), 57);
    sfmlFunc.CreateButton(_buttonCancel, _buttonCancelText, _font, "Cancel", sf::Vector2f(200, 50), sf::Vector2f(930, 800), 57);
}

void Menu::InitCreateRoom() {
    _roomMenu.setSize(sf::Vector2f(1000, 310));
    _roomMenu.setFillColor(sf::Color::Black);
    _roomMenu.setOutlineColor(sf::Color::White);
    _roomMenu.setOutlineThickness(5.0f);
    _roomMenu.setPosition(sf::Vector2f(400, 460));
}
