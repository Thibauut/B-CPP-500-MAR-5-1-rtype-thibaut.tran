/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** main.cpp
*/

#include <iostream>
#include <thread>
#include <atomic>

#include "graphical/menu/anim.cpp"
#include "graphical/menu/handle_events.cpp"
#include "graphical/menu/handle_tcp_events.cpp"
#include "graphical/menu/init.cpp"
#include "graphical/menu.cpp"
#include "graphical/menu/tcp_func.cpp"


#include "network/ConnectionTCP/ConnectionTCP.cpp"
#include "network/OpenUDP/OpenUDP.cpp"
#include "network/ThreadHandler/ThreadHandler.hpp"
// #include "include/global.hpp"

void TimerThread(Menu* menu) {
    int counter = 0;


    while (shouldStop == false) {
        if (menu->_isConnected && !menu->_selectedRoom && !menu->_isCreatingRoom && menu->_inGame == false && menu->ReadyGame == false) {
            menu->_1Mutex.lock();
            std::cout << "update room list" << std::endl;
            menu->UpdateRoom();
            menu->_1Mutex.unlock();
        }
        if (menu->_isConnected && menu->_selectedRoom && !menu->_isCreatingRoom && menu->_inGame == false && menu->ReadyGame == false) {
            menu->_1Mutex.lock();
            std::cout << "update player list" << std::endl;
            menu->UpdateRoom();
            menu->UpdatePlayerList();
            menu->_1Mutex.unlock();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main(int ac, char **av)
{
    // TEST GRAPHIC + CLIENT
    Menu *menu = new Menu();

    std::thread timer(TimerThread, menu);

    menu->Loop();

    timer.detach();
    delete menu;

    // std::shared_ptr<ClientOpenUDP> clientudp = std::make_shared<ClientOpenUDP>("192.168.1.27", "7171");
    // std::thread th([clientudp]() {
    //     clientudp->run();
    // });
    // th.join();

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
