/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** main.cpp
*/

#include <iostream>
#include "graphical/menu.cpp"


int main(int ac, char **av)
{
    Menu *menu = new Menu();
    menu->Loop();

    return 0;
}
