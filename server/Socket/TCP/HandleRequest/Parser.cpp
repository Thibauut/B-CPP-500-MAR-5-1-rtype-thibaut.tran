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
            _args.push_back(data.substr(13, findQuote(data, 2) - findQuote(data, 1) - 1));
            _args.push_back(data.substr(posSlot + 1, findQuote(data, 4) - findQuote(data, 3) - 1));
            _args.push_back(data.substr(posName + 1, findQuote(data, 6) - findQuote(data, 5) - 1));
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
    };

    void Parser::callback(HandleSave &save, std::vector <RoomLobby> &_lobbys) {
        switch (_action) {
            case LOGIN:
                login(save);
                break;
            case DISCONNECT:
                disconnect(save);
                break;
            case GET_PLAYER_INFO:
                getPlayerInfo();
                break;
            case CREATE_ROOM:
                createRoom(_args.at(0), std::stoi(_args.at(1)), _args.at(2), save, _lobbys);
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
            default:
                break;
        }
    };

    void Parser::login(HandleSave &save) {
        if (save.PlayerExist(_args.at(0)) == false) {
            save.createPlayer(_args.at(0));
            save.save();
            std::cout << "=> LOGIN " << save.findPlayerByName(_args.at(0)).getUuid() << std::endl;
            std::string response = "LOGIN " + save.findPlayerByName(_args.at(0)).getUuid() + '\n';
            _socket.async_write_some(boost::asio::buffer(response),
            [sharedThis = this](const boost::system::error_code& error,
                size_t bytes_transferred) {
                });
        } else {
            std::cout << "-> LOGIN " << save.findPlayerByName(_args.at(0)).getUuid() << std::endl;
            std::string response = "LOGIN " + save.findPlayerByName(_args.at(0)).getUuid() + '\n';
            save.setPlayerStatus(true, save.findPlayerByName(_args.at(0)).getUuid());
            _socket.async_write_some(boost::asio::buffer(response),
            [sharedThis = this](const boost::system::error_code& error,
                size_t bytes_transferred) {});
        }
    };

    void Parser::disconnect(HandleSave &save) {
        std::cout << "-> DISCONNECT " << save.findPlayerByUuid(_args.at(0)).getUuid() << std::endl;
        std::string response = "DISCONNECT OK\n";
        save.setPlayerStatus(false, save.findPlayerByUuid(_args.at(0)).getUuid());
        save.save();
        _socket.async_write_some(boost::asio::buffer(response),
            [sharedThis = this](const boost::system::error_code& error,
                size_t bytes_transferred) {});
    }

    void Parser::createRoom(std::string player_uuid, int nb_slots, std::string name, HandleSave &save, std::vector <RoomLobby> &_lobbys) {
        std::string room_uuid = boost::uuids::to_string(boost::uuids::random_generator()());
        _lobbys.push_back(RoomLobby(save.findPlayerByUuid(player_uuid), nb_slots, name, room_uuid));
        std::string response = "CREATE_ROOM " + room_uuid + "\n";
        std::cout << "-> " << response;
        _socket.async_write_some(boost::asio::buffer(response),
            [sharedThis = this](const boost::system::error_code& error,
                size_t bytes_transferred) {});
    }

    void Parser::joinRoom(std::string player_uuid, std::string room_uuid) {
        std::cout << "-> JOIN_ROOM OK\n" << std::endl;
        std::string response = "JOIN_ROOM OK\n";
        _socket.async_write_some(boost::asio::buffer(response),
            [sharedThis = this](const boost::system::error_code& error,
                size_t bytes_transferred) {});
    }

    void Parser::leaveRoom(std::string player_uuid, std::string room_uuid) {
        std::cout << "-> LEAVE_ROOM OK\n" << std::endl;
        std::string response = "LEAVE_ROOM OK\n";
        _socket.async_write_some(boost::asio::buffer(response),
            [sharedThis = this](const boost::system::error_code& error,
                size_t bytes_transferred) {});
    }

    void Parser::deleteRoom(std::string player_uuid, std::string room_uuid) {
        std::cout << "-> DELETE_ROOM OK\n" << std::endl;
        std::string response = "DELETE_ROOM OK\n";
        _socket.async_write_some(boost::asio::buffer(response),
            [sharedThis = this](const boost::system::error_code& error,
                size_t bytes_transferred) {});
    }

    void Parser::ready(std::string player_uuid, std::string room_uuid) {
        std::cout << "-> READY OK\n" << std::endl;
        std::string response = "READY OK\n";
        _socket.async_write_some(boost::asio::buffer(response),
            [sharedThis = this](const boost::system::error_code& error,
                size_t bytes_transferred) {});
    }