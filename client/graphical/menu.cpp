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

            _game->gameEngine_.addSystem(std::make_shared<SysAnimation>(_game->gameEngine_.getManager()));
            _game->gameEngine_.addSystem(std::make_shared<SysClearClient>(_game->gameEngine_.getManager()));

            _game->my_player = std::make_shared<Entity>(std::atoi(_game->my_id_.c_str()), 1);
            _game->my_player->init();

            //id & port initialize
            _game->my_id_ = start_id_;
            _game->portUDP_ = start_port_;
            std::cout << "my id: " << _game->my_id_ << std::endl;
            std::cout << "game port: " << _game->portUDP_ << std::endl;

            std::shared_ptr<ClientOpenUDP> clientudp = std::make_shared<ClientOpenUDP>(_inputIp, _game->portUDP_, _game->gameEngine_._manager, _game->my_id_);
            _game->_clientOpenUDP = clientudp;


            std::thread ioThread([&] {
                clientudp->ioService.run();
            });

            std::thread thGameEngine([&] {
                _game->gameEngine_.run();
            });

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            clientudp->init(_game->my_player);
            _game->my_player->getComponentByType<Sprite>(CONFIG::CompType::SPRITE)->initSprite();
            std::thread th([clientudp, my_id = _game->my_player->getId()]() {
                clientudp->run(my_id);
            });

            _game->Loop();

            // delete _game;
            // _inGame = false;
            thGameEngine.join();
            th.join();
            ioThread.join();
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

        _window->draw(_previous_GameType_choose);
        _window->draw(_text_GameType_choose);
        _window->draw(_next_GameType_choose);

        _window->draw(_buttonCancel);
        _window->draw(_buttonCancelText);
        if (_Game_Type == 0 || _Game_Type == 3 || _Game_Type == 4) {
            _window->draw(_textField2_room);
            _window->draw(_text_slot_room);
            _window->draw(_text_slot_input_room);
            _window->draw(_addSlot);
            _window->draw(_removeSlot);
            _window->draw(_previous_level_choose);
            _window->draw(_text_level_choose);
            _window->draw(_next_level_choose);
        }
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