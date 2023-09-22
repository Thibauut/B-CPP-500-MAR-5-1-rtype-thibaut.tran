/*
** EPITECH PROJECT, 2023
** Visual Studio Live Share (Workspace)
** File description:
** Parser.hpp
*/

#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "TCPRequest.hpp"
#include <boost/asio.hpp>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>

enum ACTION {
    LOGIN,
    DISCONNECT,
    GET_PLAYER_INFO,
    CREATE_ROOM,
    JOIN_ROOM,
    READY,
};

class Parser {
private:
    int findSpace(std::string data, int nbOccur) {
        int pos = 0;
        int nb = 0;

        for (int i = 0; i < data.size(); i++) {
            if (data[i] == ' ') {
                nb++;
                if (nb == nbOccur) {
                    pos = i;
                    break;
                }
            }
        }
        return pos;
    };

    void parseAction(std::string data) {
        if (data.find("LOGIN") != std::string::npos) {
            _action = LOGIN;
            _args.push_back(data.substr(6));
        }
        if (data.find("DISCONNECT") != std::string::npos) {
            _action = DISCONNECT;
            _args.push_back(data.substr(11));
        }
        if (data.find("GET_PLAYER_INFO") != std::string::npos) {
            _action = GET_PLAYER_INFO;
            _args.push_back(data.substr(16));
        }
        if (data.find("CREATE_ROOM") != std::string::npos) {
            _action = CREATE_ROOM;
            int posId = findSpace(data, 1);
            int posSlot = findSpace(data, 2);
            int posName = findSpace(data, 3);
            _args.push_back(data.substr(posId, posSlot - 12));
            _args.push_back(data.substr(posSlot + 1, posName - posId - 1));
            _args.push_back(data.substr(posName + 1, data.length() - posSlot - 1));
        }
        if (data.find("JOIN_ROOM") != std::string::npos) {
            _action = JOIN_ROOM;
            int posId = findSpace(data, 1);
            int posRoomId = findSpace(data, 2);
            _args.push_back(data.substr(posId, posRoomId - 9));
            _args.push_back(data.substr(posRoomId + 1, data.length() - posRoomId - 1));
        }
        if (data.find("READY") != std::string::npos) {
            _action = READY;
            int posId = findSpace(data, 1);
            int posRoomId = findSpace(data, 2);
            _args.push_back(data.substr(posId, posRoomId - 6));
            _args.push_back(data.substr(posRoomId + 1, data.length() - posRoomId - 1));
        }
    };

    void callback() {
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
                createRoom();
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

    void login() {
        boost::uuids::uuid _uuid = boost::uuids::random_generator()();
        std::string uuid = "LOGIN " + boost::uuids::to_string(_uuid) + "\n";
        _socket.async_write_some(boost::asio::buffer(uuid),
            [uuid_generated = _uuid](const boost::system::error_code& error,
                size_t bytes_transferred) {
                    std::cout << "=> LOGIN " << uuid_generated << std::endl;
            });
    };
    void disconnect() {};
    void getPlayerInfo() {};
    void createRoom() {};
    void joinRoom() {};
    void ready() {};

    ACTION _action;
    std::vector<std::string> _args;
    boost::asio::ip::tcp::socket &_socket;
public:
    Parser(Request request) : _socket(request._socket) {
        parseAction(request._data);
        callback();
    };
    ~Parser() {};
};
