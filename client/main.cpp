/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** main.cpp
*/

#include <iostream>
#include "graphical/menu/init.cpp"
#include "graphical/menu.cpp"
#include "graphical/menu/anim.cpp"
#include "graphical/menu/handle_events.cpp"
#include "graphical/menu/handle_tcp_events.cpp"
#include "graphical/menu/tcp_func.cpp"



#include "network/ConnectionTCP/ConnectionTCP.hpp"
#include "network/OpenUDP/OpenUDP.hpp"
#include "network/ThreadHandler/ThreadHandler.hpp"

int main(int ac, char **av)
{
    // TEST GRAPHIC + CLIENT
    Menu *menu = new Menu();
    menu->Loop();

    // TEST CLIENT WHITOUT GRAPHIC
    // ClientConnectionTCP *client = new ClientConnectionTCP("test", "192.168.0.22", "12345");
    // // client->start();
    // client->Login();
    // client->CreateRoom("test 1", "2");

    // client->GetRoomList();
    // // client->GetRoomInfo(client->infoRoomUuid_);
    // // // client->JoinRoom(client->infoRoomUuid_);
    // // client->Ready();
    // client->LeaveRoom(client->infoRoomUuid_);
    // client->DeleteRoom(client->infoRoomUuid_);

    // client->Disconnect();
    // client->stop();

    return 0;
}
