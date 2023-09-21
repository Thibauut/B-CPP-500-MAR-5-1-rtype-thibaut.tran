/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** LaunchServer.cpp
*/

#include "Server.hpp"

int main ()
{
    try {
        boost::asio::io_context context;
        Server server(context, 4000);
        context.run();
    } catch (std::exception &e) {
        std::cerr << "Error in main: " << e.what() << std::endl;
        return (84);
    }
    return (0);
}