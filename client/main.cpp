/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** main.cpp
*/

#include <iostream>
#include "graphical/init.cpp"
#include "graphical/menu.cpp"
#include "graphical/anim.cpp"


#include "network/ConnectionTCP/ConnectionTCP.hpp"
#include "network/OpenUDP/OpenUDP.hpp"
#include "network/ThreadHandler/ThreadHandler.hpp"

int main(int ac, char **av)
{
    // TEST GRAPHIC + CLIENT
    // Menu *menu = new Menu();
    // menu->Loop();

    // TEST CLIENT WHITOUT GRAPHIC
    ClientConnectionTCP *client = new ClientConnectionTCP("test", "192.168.0.30", "12345");
    // client->start();
    client->Login();
    client->CreateRoom();
    client->JoinRoom();
    client->Ready();
    client->LeaveRoom();
    client->DeleteRoom();

    client->stop();

    return 0;
}
