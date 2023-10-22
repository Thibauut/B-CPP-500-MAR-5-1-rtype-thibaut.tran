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
            menu->UpdateRoom();
            menu->_1Mutex.unlock();
        }
        if (menu->_isConnected && menu->_selectedRoom && !menu->_isCreatingRoom && menu->_inGame == false && menu->ReadyGame == false) {
            menu->_1Mutex.lock();
            menu->UpdateRoom();
            menu->UpdatePlayerList();
            menu->_1Mutex.unlock();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main(int ac, char **av)
{
    Menu *menu = new Menu("127.0.0.1", "12345");
    std::thread timer(TimerThread, menu);
    menu->Loop();
    timer.detach();
    delete menu;
    return 0;
}
