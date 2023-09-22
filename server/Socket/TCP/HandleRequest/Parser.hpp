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
#include "../TCPRequest.hpp"
#include <boost/asio.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "../../../Save/HandleSave.hpp"

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
};

class Parser {
private:
    int findQuote(std::string data, int nbOccur);
    void parseAction(std::string data);
    void callback(HandleSave &save, std::vector <RoomLobby> &_lobbys);

    void login(HandleSave &save);
    void disconnect(HandleSave &save);
    void getPlayerInfo() {};

    void createRoom(std::string player_uuid,
                    int nb_slots, std::string name,
                    HandleSave &save,
                    std::vector <RoomLobby> &_lobbys);
    void joinRoom(std::string player_uuid, std::string room_uuid);
    void leaveRoom(std::string player_uuid, std::string room_uuid);
    void deleteRoom(std::string player_uuid, std::string room_uuid);
    void ready(std::string player_uuid, std::string room_uuid);

    ACTION _action;
    std::vector<std::string> _args;
    boost::asio::ip::tcp::socket &_socket;

public:
    Parser(Request request, HandleSave &save, std::vector <RoomLobby> &_lobbys) : _socket(request._socket) {
        parseAction(request._data);
        callback(save, _lobbys);
    };
    ~Parser() {};
};
