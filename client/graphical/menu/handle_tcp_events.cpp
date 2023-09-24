/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** handle_tcp_events.cpp
*/

#include "../../include/menu.hpp"

void Menu::HandleTcpEvents()
{
    if (_event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window));
        sf::FloatRect buttonBounds = _button.getGlobalBounds();
        sf::FloatRect buttonCreateBounds = _buttonCreate.getGlobalBounds();
        sf::FloatRect buttonDisconnectBounds = _buttonDisconnect.getGlobalBounds();
        sf::FloatRect addSlotBounds = _addSlot.getGlobalBounds();
        sf::FloatRect removeSlotBounds = _removeSlot.getGlobalBounds();
        sf::FloatRect buttonLeaveBounds = _buttonLeave.getGlobalBounds();
        sf::FloatRect buttonDeleteBounds = _roomDelete.getGlobalBounds();
        sf::FloatRect buttonCreateRoomBounds = _buttonCreateRoom.getGlobalBounds();
        sf::FloatRect buttonCancelRoomBounds = _buttonCancel.getGlobalBounds();
        sf::FloatRect buttonReadyBounds = _buttonReady.getGlobalBounds();

        //////////////////////////////////////////////////////
        //                  CONFIGURE SLOT                  //
        //////////////////////////////////////////////////////
        if (addSlotBounds.contains(mousePos) && _isCreatingRoom && _roomSlot < 11) {
            _roomSlot++;
            _text_slot_input_room.setString(std::to_string(_roomSlot));
        }
        if (removeSlotBounds.contains(mousePos) && _isCreatingRoom) {
            if (_roomSlot > 1) {
                _roomSlot--;
                _text_slot_input_room.setString(std::to_string(_roomSlot));
            }
        }

        //////////////////////////////////////////////////////
        //                      LOGIN                       //
        //////////////////////////////////////////////////////
        if (buttonBounds.contains(mousePos)) {
            // _tcpConnection = new ClientConnectionTCP(_text_name_input.getString().toAnsiString(),
            //                                         _text_ip_input.getString().toAnsiString(),
            //                                         _text_port_input.getString().toAnsiString());
            // std::cout << _tcpConnection->ip_ << std::endl;
            // std::cout << _tcpConnection->port_ << std::endl;
            // std::cout << _tcpConnection->username_ << std::endl;
            // _tcpConnection->Login();

            // if (!_tcpConnection->uuid_.empty()) {
            //     _isConnected = true;
            //     Player_uuid_ = _tcpConnection->uuid_;
            //     UpdateRoom();
            //     std::cout << "Connect" << std::endl;
            // }
            ClientConnectionTCP* _tcpConnection = new ClientConnectionTCP(
                _text_name_input.getString().toAnsiString(),
                _text_ip_input.getString().toAnsiString(),
                _text_port_input.getString().toAnsiString()
            );
            std::thread tcpThread(&ClientConnectionTCP::Login, _tcpConnection);
            tcpThread.join();
            if (!_tcpConnection->uuid_.empty()) {
                _isConnected = true;
                Player_uuid_ = _tcpConnection->uuid_;
                UpdateRoom();
                std::cout << "Connect" << std::endl;
            }
        }


        //////////////////////////////////////////////////////
        //                    DISCONNECT                    //
        //////////////////////////////////////////////////////
        if (buttonDisconnectBounds.contains(mousePos) && _isConnected) {
            _tcpConnection->Disconnect();
            _tcpConnection->stop();
            _isConnected = false;
            std::cout << "Disconnect" << std::endl;
        }

        //////////////////////////////////////////////////////
        //                      CREATE                      //
        //////////////////////////////////////////////////////
        if (buttonCreateBounds.contains(mousePos) && _isConnected && !_isCreatingRoom && !_selectedRoom) {
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
                room->nbPlayers.setString("0/" +  _text_slot_input_room.getString().toAnsiString());
                room->nbPlayers.setCharacterSize(24);
                room->nbPlayers.setFillColor(sf::Color::White);
                room->nbPlayers.setPosition(sf::Vector2f(400, 460 + (_roomSizeIndex * _roomList.size())) + sf::Vector2f(40, 10));
                room->roomuuid = _tcpConnection->infoRoomUuid_;
                std::cout << room->roomuuid << std::endl;
                _roomList.push_back(room);
                _roomIndex++;

                _isCreatingRoom = false;
                _text_name_input_room.setString("Room 1");
                _text_slot_input_room.setString("0");
                _roomSlot = 0;
                _inputName_room = "";

                _selectedRoom = room;

            }
        }

        //////////////////////////////////////////////////////
        //                      JOIN                        //
        //////////////////////////////////////////////////////
        if (!_roomList.empty() && _isConnected && !_isCreatingRoom && !_selectedRoom) {
            UpdateRoom();
            for (auto &room : _roomList) {
                if (room->room.getGlobalBounds().contains(mousePos)) {
                    std::string res = _tcpConnection->JoinRoom(room->roomuuid, Player_uuid_);
                    if (res == "KO") {
                        std::cerr << "Error until room join" << std::endl;
                    } else {
                        _selectedRoom = room;
                        UpdatePlayerList();
                    }
                }
            }
        }

        //////////////////////////////////////////////////////
        //                      CANCEL                      //
        //////////////////////////////////////////////////////
        if (_isCreatingRoom && buttonCancelRoomBounds.contains(mousePos)) {
            _isCreatingRoom = false;
            _text_name_input_room.setString("Room 1");
            _text_slot_input_room.setString("0");
            _roomSlot = 0;
            _inputName_room = "";
            UpdateRoom();
        }

        //////////////////////////////////////////////////////
        //                      DELETE                      //
        //////////////////////////////////////////////////////
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

        //////////////////////////////////////////////////////
        //                      LEAVE                       //
        //////////////////////////////////////////////////////
        if (buttonLeaveBounds.contains(mousePos) && _isConnected && _selectedRoom && !_isCreatingRoom) {
            _tcpConnection->LeaveRoom(_selectedRoom->roomuuid);
            _selectedRoom = nullptr;
        }

        //////////////////////////////////////////////////////
        //                      READY                       //
        //////////////////////////////////////////////////////
        if (buttonReadyBounds.contains(mousePos) && _isConnected && _selectedRoom && !_isCreatingRoom) {
            std::cout << "Ready" << std::endl;
            // _tcpConnection->Ready(_selectedRoom->roomuuid, Player_uuid_);
            // UpdatePlayerList();
            _inGame = true;
        }
    }
}