/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Server.cpp
*/

#include "Server.hpp"

Server::Server(boost::asio::io_service &io_service, int port) : _menu(io_service, port), _port(port) { initServer();}

Server::~Server() {}

void Server::initServer(){}

void Server::run()
{
    while (1) {
        // cout <<"le while (1)"<< endl;
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
    try {
        boost::asio::io_service service;
        Server server(service, 1234);
        service.run();
        while (1) {}
    } catch (std::exception &e) {
        std::cerr << "Error in main: " << e.what() << std::endl;
        std::cout << "Report logs ? (Y/n)" << std::endl;
        std::cin.get();
        return (84);
    }
    return (0);
}
