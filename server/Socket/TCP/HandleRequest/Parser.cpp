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
            int posSlot = findQuote(data, 2);
            int posName = findQuote(data, 3);
            _args.push_back(data.substr(posId, posSlot - 12));
            _args.push_back(data.substr(posSlot + 1, posName - posId - 1));
            _args.push_back(data.substr(posName + 1, data.length() - posSlot - 1));
        }
        if (data.find("JOIN_ROOM") != std::string::npos) {
            _action = JOIN_ROOM;
            int posId = findQuote(data, 1);
            int posRoomId = findQuote(data, 2);
            _args.push_back(data.substr(posId, posRoomId - 9));
            _args.push_back(data.substr(posRoomId + 1, data.length() - posRoomId - 1));
        }
        if (data.find("READY") != std::string::npos) {
            _action = READY;
            int posId = findQuote(data, 1);
            int posRoomId = findQuote(data, 2);
            _args.push_back(data.substr(posId, posRoomId - 6));
            _args.push_back(data.substr(posRoomId + 1, data.length() - posRoomId - 1));
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
                joinRoom();
                break;
            case READY:
                ready();
                break;
            default:
                break;
        }
    };

    void Parser::login(HandleSave &save) {
        if (save.PlayerExist(_args.at(0)) == false) {
            save.createPlayer(_args.at(0));
            save.save();
            std::cout << "=> CREATE NEW CLIENT " << save.findPlayerByName(_args.at(0)).getUuid() << std::endl;
            std::string response = "LOGIN " + save.findPlayerByName(_args.at(0)).getUuid() + '\n';
            _socket.async_write_some(boost::asio::buffer(response),
            [sharedThis = this](const boost::system::error_code& error,
                size_t bytes_transferred) {
                });
        } else {
            std::cout << "=> LOGIN " << save.findPlayerByName(_args.at(0)).getUuid() << std::endl;
            std::string response = "LOGIN " + save.findPlayerByName(_args.at(0)).getUuid() + '\n';
            save.setPlayerStatus(true, save.findPlayerByName(_args.at(0)).getUuid());
            _socket.async_write_some(boost::asio::buffer(response),
            [sharedThis = this](const boost::system::error_code& error,
                size_t bytes_transferred) {});
        }
    };

    void Parser::disconnect(HandleSave &save) {
        std::cout << "=> DISCONNECT " << save.findPlayerByUuid(_args.at(0)).getUuid() << std::endl;
        std::string response = "DISCONNECT OK\n";
        save.setPlayerStatus(false, save.findPlayerByUuid(_args.at(0)).getUuid());
        save.save();
        _socket.async_write_some(boost::asio::buffer(response),
            [sharedThis = this](const boost::system::error_code& error,
                size_t bytes_transferred) {});
    }

    void Parser::createRoom(std::string player_uuid, int nb_slots, std::string name, HandleSave &save, std::vector <RoomLobby> &_lobbys) {
        std::cout << "=> CREATE_ROOM " << _args.at(0) << " " << _args.at(1) << " " << _args.at(2) << std::endl;
        // server->createRoom(save.findPlayerByUuid(player_uuid), name, nb_slots);
        std::string response = "CREATE_ROOM OK\n";
        _socket.async_write_some(boost::asio::buffer(response),
            [sharedThis = this](const boost::system::error_code& error,
                size_t bytes_transferred) {});
    }