/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** handle_tcp_events.cpp
*/

#include "../../include/menu.hpp"

void Menu::HandleTcpEvents()
{
    if (_event.type == sf::Event::MouseButtonReleased) {
        sf::Vector2f mousePos = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window));
        sf::FloatRect buttonBounds = _button.getGlobalBounds();
        sf::FloatRect buttonCreateBounds = _buttonCreate.getGlobalBounds();
        sf::FloatRect buttonDisconnectBounds = _buttonDisconnect.getGlobalBounds();
        sf::FloatRect addSlotBounds = _addSlot.getGlobalBounds();
        sf::FloatRect nextMapBounds = _next_level_choose.getGlobalBounds();

        sf::FloatRect nextGameTypeBounds = _next_GameType_choose.getGlobalBounds();
        sf::FloatRect previousGameTypeBounds = _previous_GameType_choose.getGlobalBounds();

        sf::FloatRect previousMapBounds = _previous_level_choose.getGlobalBounds();
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
        //                      GAME TYPE                    //
        //////////////////////////////////////////////////////

        if (nextGameTypeBounds.contains(mousePos) && _isCreatingRoom && _Game_Type < 4) {
            _Game_Type++;
            if (_Game_Type == 0)
                TypeName = "Normal";
            if (_Game_Type == 1)
                TypeName = "Solo PVP";
            if (_Game_Type == 2)
                TypeName = "Duo PVP";
            if (_Game_Type == 3)
                TypeName = "Survival";
            if (_Game_Type == 4)
                TypeName = "Battle Royal";
            _text_GameType_choose.setString(TypeName);
        }
        if (previousGameTypeBounds.contains(mousePos) && _isCreatingRoom && _Game_Type > 0) {
            _Game_Type--;
             if (_Game_Type == 0)
                TypeName = "Normal";
            if (_Game_Type == 1)
                TypeName = "Solo PVP", _roomSlot = 2;
            if (_Game_Type == 2)
                TypeName = "Duo PVP", _roomSlot = 4;
            if (_Game_Type == 3)
                TypeName = "Survival";
            if (_Game_Type == 4)
                TypeName = "Battle Royal";
            _text_GameType_choose.setString(TypeName);
        }
        _text_GameType_choose.setString(TypeName);


        //////////////////////////////////////////////////////
        //                      LOGIN                       //
        //////////////////////////////////////////////////////
        if (buttonBounds.contains(mousePos) && _isConnected == false) {
            _tcpConnection = new ClientConnectionTCP(_text_name_input.getString().toAnsiString(),
                                                    _text_ip_input.getString().toAnsiString(),
                                                    _text_port_input.getString().toAnsiString());
            // std::cout << _tcpConnection->ip_ << std::endl;
            // std::cout << _tcpConnection->port_ << std::endl;
            // std::cout << _tcpConnection->username_ << std::endl;
            _tcpConnection->Login();

            if (!_tcpConnection->uuid_.empty()) {
                canLogin = false;
                _isConnected = true;
                Player_uuid_ = _tcpConnection->uuid_;
                UpdateRoom();
                // std::cout << "Connect" << std::endl;
            }
        }

        //////////////////////////////////////////////////////
        //                    DISCONNECT                    //
        //////////////////////////////////////////////////////
        if (buttonDisconnectBounds.contains(mousePos) && _isConnected && !_isCreatingRoom && !_selectedRoom) {
            _tcpConnection->Disconnect();
            _tcpConnection->stop();
            _isConnected = false;
            // std::cout << "Disconnect" << std::endl;
        }


        //////////////////////////////////////////////////////
        //                      CREATE                      //
        //////////////////////////////////////////////////////
        if (buttonCreateBounds.contains(mousePos) && _isConnected && !_isCreatingRoom && !_selectedRoom) {
            _isCreatingRoom = true;
            DIR *dir;
            struct dirent *ent;
            if ((dir = opendir("assets/maps/")) != NULL) {
                for (bool isFirst = true; (ent = readdir(dir)) != NULL; ) {
                    if (ent->d_name[0] != '.') {
                        std::string path = "assets/maps/";
                        path.append(ent->d_name);
                        if (path.find(".json") == std::string::npos)
                            continue;
                        std::ifstream input_file(path);
                        nlohmann::json map_data;
                        input_file >> map_data;
                        try {
                            std::string name = map_data["name"];
                            _maps.push_back(std::make_pair(name, path));
                            input_file.close();
                            std::cout << "Name: " << name << " path=" << path << std::endl;
                            if (isFirst)
                                _text_level_choose.setString(name);
                            isFirst = false;
                        } catch (std::exception &e) {
                            std::cerr << "Error while parsing the file " << ent->d_name << "\n" << e.what() << std::endl;
                        }
                    }
                }
                closedir(dir);
            }
        }
        if (_isCreatingRoom && nextMapBounds.contains(mousePos)) {
            if (_maps.size() > 1) {
                _mapIndex++;
                if (_mapIndex >= _maps.size())
                    _mapIndex = 0;
                _text_level_choose.setString(_maps[_mapIndex].first);
            }
        }
        if (_isCreatingRoom && previousMapBounds.contains(mousePos)) {
            if (_maps.size() > 1) {
                _mapIndex--;
                if (_mapIndex < 0)
                    _mapIndex = _maps.size() - 1;
                _text_level_choose.setString(_maps[_mapIndex].first);
            }
        }
        if (_isCreatingRoom && buttonCreateRoomBounds.contains(mousePos) && _roomSlot > 0) {
            _tcpConnection->CreateRoom(_text_name_input_room.getString().toAnsiString(), _text_slot_input_room.getString().toAnsiString(), _maps[_mapIndex].second, _Game_Type);
            if (_tcpConnection->infoRoomUuid_ == "KO") {
                std::cerr << "Error until new room create" << std::endl;
            } else {
                Room *room = new Room();
                sfmlFunc.CreateButton(room->room, room->roomText, _font, _text_name_input_room.getString().toAnsiString(), sf::Vector2f(1000, 40), sf::Vector2f(460, 460 + (_roomSizeIndex * _roomList.size())), 150);
                room->nbPlayers.setFont(_font);
                room->nbPlayers.setString("0/" +  _text_slot_input_room.getString().toAnsiString());
                room->nbPlayers.setCharacterSize(24);
                room->nbPlayers.setFillColor(sf::Color::White);
                room->nbPlayers.setPosition(sf::Vector2f(460, 460 + (_roomSizeIndex * _roomList.size())) + sf::Vector2f(40, 10));
                room->roomuuid = _tcpConnection->infoRoomUuid_;
                // std::cout << room->roomuuid << std::endl;
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
        if (!_roomList.empty() && _isConnected && !_isCreatingRoom && !_selectedRoom && !_inGame) {
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
            _1Mutex.lock();
            _tcpConnection->Ready(_selectedRoom->roomuuid, Player_uuid_, start_id_, start_port_);
            if (_tcpConnection->startGame == true && !start_id_.empty()) {
                _inGame = true;
            }
            _1Mutex.unlock();
        }
    }
}
