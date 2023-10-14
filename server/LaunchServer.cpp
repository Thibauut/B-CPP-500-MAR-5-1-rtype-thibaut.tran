/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** LaunchServer.cpp
*/

#include "Server.hpp"
#include <boost/asio.hpp>
#include <iostream>
#include "Includes.hpp"

using namespace RType;

int main ()
{
    try {
        boost::asio::io_context context;
        Server server(context, 4242);
        server.run(context);
    } catch (std::exception &e) {
        std::cerr << "Error in main: " << e.what() << std::endl;
        return (84);
    }
    return (0);
}