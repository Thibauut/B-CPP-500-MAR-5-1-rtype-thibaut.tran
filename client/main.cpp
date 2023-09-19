/*
** EPITECH PROJECT, 2023
** rtype
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
