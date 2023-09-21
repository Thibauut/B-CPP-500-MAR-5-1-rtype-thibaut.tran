/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** RoomLobby.hpp
*/

#pragma once
#include <iostream>
#include <chrono>
#include "../Thread/Thread.hpp"
#include "../Thread/func.h"

class RoomLobby {
    public:
        RoomLobby(int owner);
        ~RoomLobby();

        void join();

        int _owner;
        Thread _thread;
};