/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** menu.cpp
*/

#include "../include/menu.hpp"

Menu::Menu()
{
    Init();
    InitBackground();
    InitSprites();
    InitText();
    InitButton();
    InitCreateRoom();


    _current_input = -1;
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
            //run game
        }
    }
    _tcpConnection->Disconnect();
    delete _tcpConnection;
}

void Menu::UpdateRoom() {
    _tcpConnection->GetRoomList();
    if (!_tcpConnection->rooms.empty()) {
        for (auto &roomtcp : _tcpConnection->rooms) {
            Room *room = new Room();
            sfmlFunc.CreateButton(room->room, room->roomText, _font, roomtcp->name, sf::Vector2f(1000, 40), sf::Vector2f(400, 460 + (_roomSizeIndex * _roomList.size())), 150);
            room->nbPlayers.setFont(_font);
            room->nbPlayers.setString(roomtcp->slot);
            room->nbPlayers.setCharacterSize(24);
            room->nbPlayers.setFillColor(sf::Color::White);
            room->nbPlayers.setPosition(sf::Vector2f(400, 460 + (_roomSizeIndex * _roomList.size())) + sf::Vector2f(40, 10));
            room->roomuuid = _tcpConnection->infoRoomUuid_;
            std::cout << room->roomuuid << std::endl;
            _roomList.push_back(room);
        }
    } else {
        _roomList.clear();
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

        // anim button
        AnimButtonEvents();

        // button click
        if (_event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mousePos = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window));
            sf::FloatRect buttonBounds = _button.getGlobalBounds();

            sf::FloatRect buttonCreateBounds = _buttonCreate.getGlobalBounds();
            sf::FloatRect buttonDisconnectBounds = _buttonDisconnect.getGlobalBounds();
            sf::FloatRect buttonLeaveBounds = _buttonLeave.getGlobalBounds();
            sf::FloatRect buttonDeleteBounds = _roomDelete.getGlobalBounds();

            sf::FloatRect addSlotBounds = _addSlot.getGlobalBounds();
            sf::FloatRect removeSlotBounds = _removeSlot.getGlobalBounds();

            sf::FloatRect buttonCreateRoomBounds = _buttonCreateRoom.getGlobalBounds();
            sf::FloatRect buttonCancelRoomBounds = _buttonCancel.getGlobalBounds();

            if (addSlotBounds.contains(mousePos) && _isCreatingRoom && _roomSlot < 11) {
                _roomSlot++;
                _text_slot_input_room.setString(std::to_string(_roomSlot));
            }

            if (removeSlotBounds.contains(mousePos) && _isCreatingRoom) {
                if (_roomSlot > 1) {
                    _roomSlot--;
                    std::cout << "room slot :" << _roomSlot << std::endl;
                    _text_slot_input_room.setString(std::to_string(_roomSlot));
                }
            }

            if (buttonBounds.contains(mousePos)) {
                _tcpConnection = new ClientConnectionTCP(_text_name_input.getString().toAnsiString(),
                                                        _text_ip_input.getString().toAnsiString(),
                                                        _text_port_input.getString().toAnsiString());
                std::cout << _tcpConnection->ip_ << std::endl;
                std::cout << _tcpConnection->port_ << std::endl;
                std::cout << _tcpConnection->username_ << std::endl;
                _tcpConnection->Login();

                if (!_tcpConnection->uuid_.empty()) {
                    _isConnected = true;
                    UpdateRoom();
                    std::cout << "Connect" << std::endl;
                }
            }

            if (buttonDisconnectBounds.contains(mousePos) && _isConnected) {
                _tcpConnection->Disconnect();
                _tcpConnection->stop();
                _isConnected = false;
                std::cout << "Disconnect" << std::endl;
            }

            if (buttonCreateBounds.contains(mousePos) && _isConnected && !_isCreatingRoom) {
                std::cout << "Create" << std::endl;
                _isCreatingRoom = true;
            }

            if (_isCreatingRoom && buttonCreateRoomBounds.contains(mousePos) && _roomSlot > 0) {

                _tcpConnection->CreateRoom(_text_name_input_room.getString().toAnsiString(), _text_slot_input_room.getString().toAnsiString());
                if (_tcpConnection->infoRoomUuid_ == "KO") {
                    std::cerr << "Error until new room create" << std::endl;
                } else {
                    Room *room = new Room();
                    sfmlFunc.CreateButton(room->room, room->roomText, _font, _text_name_input_room.getString().toAnsiString(), sf::Vector2f(1000, 40), sf::Vector2f(400, 460 + (_roomSizeIndex * _roomList.size())), 150);
                    room->nbPlayers.setFont(_font);
                    room->nbPlayers.setString("0/" +  _text_slot_input_room.getString().toAnsiString()); // server response
                    room->nbPlayers.setCharacterSize(24);
                    room->nbPlayers.setFillColor(sf::Color::White);
                    room->nbPlayers.setPosition(sf::Vector2f(400, 460 + (_roomSizeIndex * _roomList.size())) + sf::Vector2f(40, 10));
                    room->roomuuid = _tcpConnection->infoRoomUuid_;
                    std::cout << room->roomuuid << std::endl;
                    _roomList.push_back(room);
                    _roomIndex++;


                    std::cout << "Room created" << std::endl;
                    _isCreatingRoom = false;
                    _text_name_input_room.setString("Room 1");
                    _text_slot_input_room.setString("0");
                    _roomSlot = 0;
                    _inputName_room = "";

                    _selectedRoom = room;
                    UpdateRoom();
                }
            }

            if (!_roomList.empty() && _isConnected && !_isCreatingRoom) {
                for (auto &room : _roomList) {
                    if (room->room.getGlobalBounds().contains(mousePos)) {
                        _tcpConnection->JoinRoom(room->roomuuid);
                        if (_tcpConnection->infoRoomUuid_ == "KO") {
                            std::cerr << "Error until join room" << std::endl;
                        } else {
                            std::cout << "Join room" << std::endl;
                            _selectedRoom = room;
                            UpdateRoom();
                        }
                    }
                }
            }

            if (_isCreatingRoom && buttonCancelRoomBounds.contains(mousePos)) {
                _isCreatingRoom = false;
                _text_name_input_room.setString("Room 1");
                _text_slot_input_room.setString("0");
                _roomSlot = 0;
                _inputName_room = "";
                UpdateRoom();
            }

            if (buttonDeleteBounds.contains(mousePos) && _isConnected && !_roomList.empty() && !_isCreatingRoom) {
                std::cout << "Delete" << std::endl;
                if (!_roomList.empty()) {
                    _tcpConnection->DeleteRoom(_roomList.back()->roomuuid);
                    if (_tcpConnection->infoRoomUuid_ == "KO") {
                        std::cerr << "Error until delete room" << std::endl;
                    } else {
                         delete _roomList.back();
                        _roomList.pop_back();
                        _roomIndex--;
                        UpdateRoom();
                    }
                }
            }

            if (buttonLeaveBounds.contains(mousePos) && _isConnected && _selectedRoom && !_isCreatingRoom) {
                std::cout << "Leave" << std::endl;
                _tcpConnection->LeaveRoom(_selectedRoom->roomuuid);
                UpdateRoom();
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
    }

    _window->display();
}