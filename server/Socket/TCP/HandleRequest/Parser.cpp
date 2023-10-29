/*
** EPITECH PROJECT, 2023
** Visual Studio Live Share (Workspace)
** File description:
** Parser.cpp
*/

#include "Parser.hpp"

int Parser::findQuote(std::string data, int nbOccur) {
    int pos = 0;
    int nb = 0;

    for (int i = 0; i < data.size(); i++) {
        if (data[i] == '"') {
            nb++;
            if (nb == nbOccur) {
                pos = i;
                break;
            }
        }
    }
    return pos;
};

void Parser::parseAction(std::string data) {
    if (data.find("LOGIN") != std::string::npos) {
        _action = LOGIN;
        _args.push_back(data.substr(7, data.length() - 9));
    }
    if (data.find("DISCONNECT") != std::string::npos) {
        _action = DISCONNECT;
        _args.push_back(data.substr(12, data.length() - 14));
    }
    if (data.find("GET_PLAYER_INFO") != std::string::npos) {
        _action = GET_PLAYER_INFO;
        _args.push_back(data.substr(17, data.length() - 19));
    }
    if (data.find("CREATE_ROOM") != std::string::npos) {
        _action = CREATE_ROOM;
        int posId = findQuote(data, 1);
        int posSlot = findQuote(data, 3);
        int posName = findQuote(data, 5);
        int posTypeGame = findQuote(data, 7);
        _args.push_back(data.substr(13, findQuote(data, 2) - findQuote(data, 1) - 1));
        _args.push_back(data.substr(posSlot + 1, findQuote(data, 4) - findQuote(data, 3) - 1));
        _args.push_back(data.substr(posName + 1, findQuote(data, 6) - findQuote(data, 5) - 1));
        _args.push_back(data.substr(posTypeGame + 1, findQuote(data, 8) - findQuote(data, 7) - 1));
        // if (_args.at(3) == "0") {
            int posPathMap = findQuote(data, 9);
            _args.push_back(data.substr(posPathMap + 1, findQuote(data, 10) - findQuote(data, 9) - 1));
        // }
    }
    if (data.find("JOIN_ROOM") != std::string::npos) {
        _action = JOIN_ROOM;
        int posId = findQuote(data, 1);
        int posRoomId = findQuote(data, 3);
        _args.push_back(data.substr(posId + 1, findQuote(data, 2) - findQuote(data, 1) - 1));
        _args.push_back(data.substr(posRoomId + 1, findQuote(data, 4) - findQuote(data, 3) - 1));
    }
    if (data.find("READY") != std::string::npos) {
        _action = READY;
        int posId = findQuote(data, 1);
        int posRoomId = findQuote(data, 3);
        _args.push_back(data.substr(posId + 1, findQuote(data, 2) - findQuote(data, 1) - 1));
        _args.push_back(data.substr(posRoomId + 1, findQuote(data, 4) - findQuote(data, 3) - 1));
    }
    if (data.find("LEAVE_ROOM") != std::string::npos) {
        _action = LEAVE_ROOM;
        int posId = findQuote(data, 1);
        int posRoomId = findQuote(data, 3);
        _args.push_back(data.substr(posId + 1, findQuote(data, 2) - findQuote(data, 1) - 1));
        _args.push_back(data.substr(posRoomId + 1, findQuote(data, 4) - findQuote(data, 3) - 1));
    }
    if (data.find("DELETE_ROOM") != std::string::npos) {
        _action = DELETE_ROOM;
        int posId = findQuote(data, 1);
        int posRoomId = findQuote(data, 3);
        _args.push_back(data.substr(posId + 1, findQuote(data, 2) - findQuote(data, 1) - 1));
        _args.push_back(data.substr(posRoomId + 1, findQuote(data, 4) - findQuote(data, 3) - 1));
    }
    if (data.find("START") != std::string::npos) {
        _action = START;
        int posId = findQuote(data, 1);
        int posRoomId = findQuote(data, 3);
        _args.push_back(data.substr(posId + 1, findQuote(data, 2) - findQuote(data, 1) - 1));
        _args.push_back(data.substr(posRoomId + 1, findQuote(data, 4) - findQuote(data, 3) - 1));
    }
    if (data.find("GET_ROOMS") != std::string::npos)
        _action = GET_ROOMS;
    if (data.find("GET_ROOM_INFO") != std::string::npos) {
        _action = GET_ROOM_INFO;
        int posRoomId = findQuote(data, 1);
        _args.push_back(data.substr(posRoomId + 1, findQuote(data, 2) - findQuote(data, 1) - 1));
    }
};

void Parser::callback() {
    switch (_action) {
        case LOGIN:
            login();
            break;
        case DISCONNECT:
            disconnect();
            break;
        case GET_PLAYER_INFO:
            getPlayerInfo();
            break;
        case CREATE_ROOM:
            createRoom(_args.at(0), std::stoi(_args.at(1)), _args.at(2), _args.at(4), std::stoi(_args.at(3)));
            break;
        case JOIN_ROOM:
            joinRoom(_args.at(0), _args.at(1));
            break;
        case READY:
            ready(_args.at(0), _args.at(1));
            break;
        case DELETE_ROOM:
            deleteRoom(_args.at(0), _args.at(1));
            break;
        case LEAVE_ROOM:
            leaveRoom(_args.at(0), _args.at(1));
            break;
        case GET_ROOMS:
            getRooms();
            break;
        case GET_ROOM_INFO:
            getRoomInfo(_args.at(0));
            break;
        case START:
            start(_args.at(0), _args.at(1));
            break;
        default:
            break;
    }
};

void Parser::login() {
    if (_server->_save.PlayerExist(_args.at(0)) == false) {
        for (std::shared_ptr<PlayerLobby>& player : _server->players_) {
            if (player.get()->connection.get()->uuid() == _request._uuid) {
                PlayerLobby pl = _server->_save.createPlayer(_args.at(0), player.get()->connection);
                player.get()->setPlayerLobby(pl);
                _server->_save.save();
                std::cout << "=> LOGIN " << _server->_save.findPlayerByName(_args.at(0)).get()->getUuid() << std::endl;
                std::string response = "LOGIN " + _server->_save.findPlayerByName(_args.at(0)).get()->getUuid() + '\n';
                _socket.async_write_some(boost::asio::buffer(response),
                [sharedThis = this](const boost::system::error_code& error,
                    size_t bytes_transferred) {});
        }}
    } else {
        for (std::shared_ptr<PlayerLobby>& player : _server->players_) {
            if (player.get()->connection.get()->uuid() == _request._uuid) {
                std::shared_ptr<PlayerLobby> pl = _server->_save.findPlayerByName(_args.at(0));
                player->setPlayerLobbyShared(pl);
                std::string response = "LOGIN " + _server->_save.findPlayerByName(_args.at(0)).get()->getUuid() + '\n';
                std::cout << "-> LOGIN " << _server->_save.findPlayerByName(_args.at(0)).get()->getUuid() << std::endl;
                _server->_save.setPlayerStatus(true, _server->_save.findPlayerByName(_args.at(0)).get()->getUuid());
                _socket.async_write_some(boost::asio::buffer(response),
                [sharedThis = this](const boost::system::error_code& error,
                    size_t bytes_transferred) {});
        }}}
};

void Parser::disconnect() {
    std::cout << "-> DISCONNECT " << _server->_save.findPlayerByUuid(_args.at(0)).get()->getUuid() << std::endl;
    std::string response = "DISCONNECT OK\n";
    _server->_save.setPlayerStatus(false, _server->_save.findPlayerByUuid(_args.at(0)).get()->getUuid());
    _server->_save.save();
    _socket.async_write_some(boost::asio::buffer(response),
        [sharedThis = this](const boost::system::error_code& error,
            size_t bytes_transferred) {});
}

void Parser::createRoom(std::string player_uuid, int nb_slots, std::string name, std::string pathMap, int gameType) {
    for (std::shared_ptr<RoomLobby> room : _server->_lobbys) {
        if (room->getName() == name) {
            std::string response = "CREATE_ROOM KO\n";
            std::cout << "-> " << response;
            _socket.async_write_some(boost::asio::buffer(response),
                [sharedThis = this](const boost::system::error_code& error,
                    size_t bytes_transferred) {});
            return;
        }
        if (room->getOwner().get()->getUuid() == player_uuid) {
            std::string response = "CREATE_ROOM KO\n";
            std::cout << "-> " << response;
            _socket.async_write_some(boost::asio::buffer(response),
                [sharedThis = this](const boost::system::error_code& error,
                    size_t bytes_transferred) {});
            return;
        }
    }

    std::string room_uuid = boost::uuids::to_string(boost::uuids::random_generator()());
    for (std::shared_ptr<PlayerLobby> player : _server->players_) {
        if (player->getUuid() == player_uuid) {
            _server->_lobbys.push_back(std::make_shared<RoomLobby>(player, nb_slots, name, room_uuid, pathMap, gameType));
            std::string response = "CREATE_ROOM " + room_uuid + "\n";
            std::cout << "-> " << response;
            _socket.async_write_some(boost::asio::buffer(response),
                [sharedThis = this](const boost::system::error_code& error,
                    size_t bytes_transferred) {});
            return;
        }
    }
}

void Parser::joinRoom(std::string player_uuid, std::string room_uuid) {
    for (std::shared_ptr<RoomLobby> room : _server->_lobbys) {
        if (room->getUuid() == room_uuid) {
            if (room->getNbPlayers() < room->getNbSlots()) {
                for (std::shared_ptr<PlayerLobby> player : _server->players_) {
                    if (player->getUuid() == player_uuid) {
                        room->addPlayer(player);
                        std::string response = "JOIN_ROOM OK\n";
                        std::cout << "-> " << response;
                        _socket.async_write_some(boost::asio::buffer(response),
                            [sharedThis = this](const boost::system::error_code& error,
                                size_t bytes_transferred) {});
                    }
                }
                return;
            } else {
                std::string response = "JOIN_ROOM KO\n";
                std::cout << "-> " << response;
                _socket.async_write_some(boost::asio::buffer(response),
                    [sharedThis = this](const boost::system::error_code& error,
                        size_t bytes_transferred) {});
                return;
            }
            break;
        }
    }
     std::string response = "JOIN_ROOM KO\n";
        std::cout << "-> " << response;
        _socket.async_write_some(boost::asio::buffer(response),
            [sharedThis = this](const boost::system::error_code& error,
                size_t bytes_transferred) {});
}

void Parser::leaveRoom(std::string player_uuid, std::string room_uuid) {
    int i  = 0;
    for (std::shared_ptr<RoomLobby> room : _server->_lobbys) {
        if (room.get()->getUuid() == room_uuid) {
            room.get()->removePlayer(player_uuid);
            if (room.get()->getNbPlayers() <= 0) {
                room.get()->stopGame();
                _server->_lobbys.erase(_server->_lobbys.begin() + i);
            }
            std::string response = "LEAVE_ROOM OK\n";
            _socket.async_write_some(boost::asio::buffer(response),
                [responseMessage = response](const boost::system::error_code& error,
                    size_t bytes_transferred) {
                            std::cout << "-> " << responseMessage;
                    });
            return;
        }
        i++;
    }
}

void Parser::deleteRoom(std::string player_uuid, std::string room_uuid) {
    if (_server->deleteLobby(room_uuid)) {
    // _server->_lobbys.at(i).get()->stopGame();
        std::string response = "DELETE_ROOM OK\n";
        _socket.async_write_some(boost::asio::buffer(response),
        [response = response](const boost::system::error_code& error,
            size_t bytes_transferred) {
                std::cout << "-> " << response;
        });
    } else {
        std::string response = "DELETE_ROOM KO\n";
        _socket.async_write_some(boost::asio::buffer(response),
            [response = response] (const boost::system::error_code& error, size_t bytes_transferred) {
                std::cout << "-> " << response;
            }
        );
    }
}

void Parser::ready(std::string player_uuid, std::string room_uuid) {
    for (std::shared_ptr<RoomLobby> room : _server->_lobbys) {
        if (room->getUuid() == room_uuid) {
            std::string response = "READY OK\n";
            std::cout << "-> " << response;
            _socket.write_some(boost::asio::buffer(response));
            // room->addReadyPlayer();
            return;
        }
    }
}

void Parser::start(std::string player_uuid, std::string room_uuid) {
    for (std::shared_ptr<RoomLobby> room : _server->_lobbys) {
        if (room->getUuid() == room_uuid) {
            if (room->addReadyPlayer()) {
                int id = 1;
                if (!room->isStarted())
                    room->startGame();
                for (std::shared_ptr<PlayerLobby> player : room->getPlayers()) {
                        std::cout << "Player in room: " << player.get()->getUsername() << std::endl;
                        std::string response = "START " + std::to_string(id) + " " + std::to_string(room->getPort()) + "\n";
                        std::cout << "READ THIS NOOB ! :" << response << " on " << player->connection->uuid() << std::endl;
                        player->connection->socket().write_some(boost::asio::buffer(response));
                        std::cout << "-> " << response;
                        id++;
                }
            }
        }
    }
}

void Parser::getRooms() {
    std::string response = "GET_ROOMS ";
    for (std::shared_ptr<RoomLobby> room : _server->_lobbys) {
        if (room != _server->_lobbys.back())
            response += "\"" + room.get()->getName() + "\" \"" + std::to_string(room.get()->getNbPlayers())  + "/" + std::to_string(room.get()->getNbSlots()) + "\" \"" + room.get()->getUuid() + "\" ";
        else
            response += "\"" + room.get()->getName() + "\" \"" + std::to_string(room.get()->getNbPlayers())  + "/" + std::to_string(room.get()->getNbSlots()) + "\" \"" + room.get()->getUuid() + "\"";
    }
    response += "\n";
    std::cout << "-> " << response;
    _socket.async_write_some(boost::asio::buffer(response),
        [sharedThis = this](const boost::system::error_code& error,
            size_t bytes_transferred) {});
}

void Parser::getRoomInfo(std::string room_uuid) {
    for (std::shared_ptr<RoomLobby> room : _server->_lobbys) {
        if (room->getUuid() == room_uuid) {
            std::string response = "GET_ROOM_INFO " + room.get()->getInfo();
            std::cout << "-> " << response;
            _socket.async_write_some(boost::asio::buffer(response),
                [sharedThis = this](const boost::system::error_code& error,
                    size_t bytes_transferred) {});
            return;
        }
    }
}