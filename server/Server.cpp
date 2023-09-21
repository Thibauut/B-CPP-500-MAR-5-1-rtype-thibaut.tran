/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Server.cpp
*/

#include "Server.hpp"

Server::Server(boost::asio::io_context& io_context, int port) : _menu(io_context), _port(port) { initServer();}

Server::~Server() {}

void Server::initServer(){}

void Server::run(boost::asio::io_context &context)
{
     try {
        std::thread refresh_thread(&Server::refresh, this);
        context.run();
        refresh_thread.join();
    } catch (std::exception &e) {}
}

void Server::refresh()
{
    while (1) {
        _menu.get_All_Tcp_Request();
    }
}

void Server::createRoom()
{
    // _lobbys.push_back(UDPSocket(_service, _port));
}

void Server::addClientToRoom(int pos, int client)
{
    // _lobbys[pos].addClient(client);
}

void Server::deleteRoom(int pos)
{
    // _lobbys.erase(_lobbys.begin() + pos);
}

int main ()
{
    boost::asio::io_context context;
    Server server(context, 4000);
    server.run(context);
    return (0);
}
