/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** menu.cpp
*/

#include "../include/menu.hpp"

Menu::Menu(std::string IP, std::string PORT): _inputIp(IP), _inputPort(PORT)
{
    Init();
    InitBackground();
    InitSprites();
    InitText();
    InitButton();
    InitCreateRoom();

    _current_input = -1;
     canLogin = true;
    _isFocused = false;
    _isFocused2 = false;
    _isFocused3 = false;
}

void Menu::Loop()
{
    while (_window->isOpen()) {
        if (!_inGame) {
            HandleEvents();
            AnimateBackground();
            Draw();
        } else {
            _game = new Game(_window);

            _game->playersEntity_ = std::vector<std::shared_ptr<Entity>>();

            _game->my_id_ = start_id_;
            _game->portUDP_ = start_port_;
            std::cout << "my id: " << _game->my_id_ << std::endl;
            std::cout << "my port: " << _game->portUDP_ << std::endl;
            std::shared_ptr<ClientOpenUDP> clientudp = std::make_shared<ClientOpenUDP>(_inputIp, _game->portUDP_, _game->playersEntity_, _game->my_id_);
            _game->_clientOpenUDP = clientudp;

            std::thread th([clientudp]() {
                clientudp->run();
            });

            _game->Loop();

            // delete _game;
            // _inGame = false;
            th.join();
        }
    }
    _tcpConnection->stop();
    delete _tcpConnection;
}

void Menu::HandleEvents() {
    while (_window->pollEvent(_event)) {
        if (_event.type == sf::Event::Closed) {
            if (_isConnected) {
                if(_selectedRoom)
                    _tcpConnection->LeaveRoom(_selectedRoom->roomuuid);
                _tcpConnection->Disconnect();
            }
            _window->close();
        }
        HandleEventsFocus();
        HandleEventText();
        AnimButtonEvents();
        HandleTcpEvents();
    }
}

void Menu::Draw() {
    _window->clear(sf::Color::Black);
    _window->draw(_background);
    _window->draw(_background2);
    _window->draw(_title);

    // _window->draw(_buttonReady);
    // _window->draw(_buttonReadyText);

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
    if (_isConnected && !_selectedRoom && !_isCreatingRoom) {
        _window->draw(_roomMenu);
        _window->draw(_buttonCreate);
        _window->draw(_buttonCreateText);
        _window->draw(_buttonDisconnect);
        _window->draw(_buttonDisconnectText);
        _window->draw(_roomDelete);

        for (auto &room : _roomList) {
            _window->draw(room->room);
            _window->draw(room->roomText);
            _window->draw(room->nbPlayers);
        }
    }
    if (_isConnected && _isCreatingRoom && !_selectedRoom) {
        _window->draw(_buttonCreateRoom);
        _window->draw(_buttonCreateRoomText);

        _window->draw(_textField_room);
        _window->draw(_text_name_room);
        _window->draw(_text_name_input_room);

        _window->draw(_textField2_room);
        _window->draw(_text_slot_room);
        _window->draw(_text_slot_input_room);

        _window->draw(_addSlot);
        _window->draw(_removeSlot);

        _window->draw(_buttonCancel);
        _window->draw(_buttonCancelText);
    }
    if (_isConnected && _selectedRoom && !_isCreatingRoom) {
        _window->draw(_roomMenu);
        _window->draw(_buttonLeave);
        _window->draw(_buttonLeaveText);
        _window->draw(_buttonReady);
        _window->draw(_buttonReadyText);

        for (auto &player : _playerList) {
            _window->draw(player->room);
            _window->draw(player->playerName);
            _window->draw(player->playerLevel);
        }
    }

    _window->display();
}