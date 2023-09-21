/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Room.cpp
*/

#include "RoomLobby.hpp"

RoomLobby::RoomLobby(int owner)
{
    _owner = owner;
    _thread.setStatus(STARTED);
    _thread.create((void *(*)(void *)) &gameThread, this);
}

RoomLobby::~RoomLobby() {}

void RoomLobby::join()
{
    _thread.join();
}

// RoomLobby::RoomLobby(int owner)
// {
//     this->owner = owner;
//     _thread = Thread([this](){
//         while (true) {
//             std::cout << "RoomLobby" << std::endl;
//             std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//         }
//     });
// }    while (true) {


