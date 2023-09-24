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
            std::string roomuuid;
        };

        Menu();
        ~Menu() = default;

        void Init();
        void InitBackground();
        void InitSprites();
        void InitText();
        void InitButton();

        void InitCreateRoom();
        void InitRoom();

        void Loop();

        void HandleEvents();
        void HandleEventsRoom();
        void HandleEventsCreateRoom();

        void AnimateBackground();
        void AnimButtonEvents();
        void Draw();
        void UpdateRoom();

        SfmlFunc sfmlFunc;
        sf::RenderWindow *_window;
        sf::VideoMode _videoMode;
        sf::Event _event;
        sf::Font _font;
        sf::Clock _clock;


        std::string Player_uuid_;
        sf::Sprite _title;
        sf::Texture _titleTexture;
        sf::Sprite _background;
        sf::Texture _backgroundTexture;
        sf::IntRect _rectBackground;
        sf::Sprite _background2;
        sf::Texture _backgroundTexture2;
        sf::IntRect _rectBackground2;

        // Menu
        sf::RectangleShape _textField;
        sf::Text _text_name;
        sf::Text _text_name_input;
        std::string _inputName;

        sf::RectangleShape _textField2;
        sf::Text _text_ip;
        sf::Text _text_ip_input;
        std::string _inputIp;

        sf::RectangleShape _textField3;
        sf::Text _text_port;
        sf::Text _text_port_input;
        std::string _inputPort;

        int _current_input;
        bool _isFocused;
        bool _isFocused2;
        bool _isFocused3;


        sf::RectangleShape _button;
        sf::Text _buttonText;

        bool _isConnected = false;
        bool isButtonHovered = false;

        // Room
        sf::RectangleShape _buttonCreate;
        sf::Text _buttonCreateText;

        sf::RectangleShape _buttonCancel;
        sf::Text _buttonCancelText;

        sf::RectangleShape _buttonDisconnect;
        sf::Text _buttonDisconnectText;


        sf::Sprite _roomDelete;
        sf::Texture _roomDeleteTexture;

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

        bool _isCreatingRoom = false;
        sf::RectangleShape _buttonCreateRoom;
        sf::Text _buttonCreateRoomText;

        // field for creating room
        sf::RectangleShape _textField_room;
        sf::Text _text_name_room;
        sf::Text _text_name_input_room;
        std::string _inputName_room;

        sf::RectangleShape _textField2_room;
        sf::Text _text_slot_room;
        sf::Text _text_slot_input_room;
        std::string _inputSlot_room;

        sf::Sprite _addSlot;
        sf::Texture _addSlotTexture;
        sf::Sprite _removeSlot;
        sf::Texture _removeSlotTexture;

        int _roomSlot = 0;

        bool _isFocused_room = false;
        bool _isFocused2_room = false;

        ClientConnectionTCP* _tcpConnection;

        int _selectedRoomIndex = -1;
};