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
#include "../TCPServer.hpp"

enum ACTION {
    LOGIN,
    DISCONNECT,
    GET_PLAYER_INFO,
    CREATE_ROOM,
    JOIN_ROOM,
    READY,
    LEAVE_ROOM,
    DELETE_ROOM,
    GET_ROOMS,
    GET_ROOM_INFO,
    START,
};

class Parser {
private:
    int findQuote(std::string data, int nbOccur);
    void parseAction(std::string data);
    void callback();

    void login();
    void disconnect();
    void getPlayerInfo() {};

    void createRoom(std::string player_uuid, int nb_slots, std::string name, std::string pathMap, int GameType);
    void joinRoom(std::string player_uuid, std::string room_uuid);
    void leaveRoom(std::string player_uuid, std::string room_uuid);
    void deleteRoom(std::string player_uuid, std::string room_uuid);
    void getRooms();
    void getRoomInfo(std::string room_uuid);
    void ready(std::string player_uuid, std::string room_uuid);
    void start(std::string player_uuid, std::string room_uuid);

    TCPServer *_server;
    ACTION _action;
    std::vector<std::string> _args;
    boost::asio::ip::tcp::socket &_socket;
    Request _request;

public:
    Parser(Request request, TCPServer *server) : _request(request), _socket(request._socket), _server(server) {
        parseAction(request._data);
        callback();
    };
    ~Parser() {};

};
