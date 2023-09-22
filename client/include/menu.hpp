/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** menu.hpp
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
#include "../graphical/utils/sfml_func.cpp"
#include "../network/ConnectionTCP/ConnectionTCP.hpp"

#define DEFAULT_WINDOW_WIDTH 1920
#define DEFAULT_WINDOW_HEIGHT 1080
#define MENU_TITLE  "R-Type"

class Menu {
    public:

        struct Room {
            sf::RectangleShape room;
            sf::Text roomText;
            sf::Text leaveText;
            sf::Text nbPlayers;
        };

        Menu();
        ~Menu() = default;
        void Loop();
        void HandleEvents();
        void AnimateBackground();
        void Draw();
        void SetTcpConnection(ClientConnectionTCP *tcpConnection) {
            _tcpConnection = tcpConnection;
        };

        SfmlFunc sfmlFunc;
        sf::RenderWindow *_window;
        sf::VideoMode _videoMode;
        sf::Event _event;
        sf::Font _font;
        sf::Clock _clock;


        sf::Sprite _title;
        sf::Texture _titleTexture;
        sf::Sprite _background;
        sf::Texture _backgroundTexture;
        sf::IntRect _rectBackground;
        sf::Sprite _background2;
        sf::Texture _backgroundTexture2;
        sf::IntRect _rectBackground2;

        sf::RectangleShape _textField;
        sf::Text _text_name;
        sf::Text _text_name_input;

        sf::RectangleShape _textField2;
        sf::Text _text_ip;
        sf::Text _text_ip_input;

        sf::RectangleShape _textField3;
        sf::Text _text_port;
        sf::Text _text_port_input;

        int _current_input = 0;
        bool _isFocused = false;
        bool _isFocused2 = false;
        bool _isFocused3 = false;

        std::string _inputName;
        std::string _inputIp;
        std::string _inputPort;

        sf::RectangleShape _button;
        sf::Text _buttonText;

        bool _isConnected = false;
        bool isButtonHovered = false;

        sf::RectangleShape _buttonCreate;
        sf::Text _buttonCreateText;
        sf::RectangleShape _buttonDisconnect;
        sf::Text _buttonDisconnectText;
        sf::RectangleShape _buttonDelete;
        sf::Text _buttonDeleteText;

        sf::RectangleShape _buttonLeave;
        sf::Text _buttonLeaveText;
        sf::RectangleShape _buttonReady;
        sf::Text _buttonReadyText;

        sf::RectangleShape _roomMenu;
        std::vector<Room *> _roomList;
        int _roomIndex = 1;
        int _roomSizeIndex = 45;

        Room* _selectedRoom = nullptr;
        bool _isFirstBackspacePress = true;

        bool _inGame;

        ClientConnectionTCP* _tcpConnection;
};