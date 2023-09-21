/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Room.cpp
*/

#pragma once
#include "Room.hpp"
#include "RoomLobby.hpp"

void gameThread(void *arg)
{
    std::cout << "Room started" << std::endl;
    RoomLobby *roomLobby = (RoomLobby *)arg;
    Room room = Room();
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}