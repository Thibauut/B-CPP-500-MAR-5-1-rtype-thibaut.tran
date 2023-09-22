/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** main.cpp
*/

#include <iostream>
#include "graphical/menu.cpp"


#include "network/ConnectionTCP/ConnectionTCP.hpp"
#include "network/OpenUDP/OpenUDP.hpp"
#include "network/ThreadHandler/ThreadHandler.hpp"

int main(int ac, char **av)
{
    Menu *menu = new Menu();
    menu->Loop();
    return 0;
}
