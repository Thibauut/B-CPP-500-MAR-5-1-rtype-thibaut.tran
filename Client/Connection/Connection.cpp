/*
** EPITECH PROJECT, 2023
** Client
** File description:
** Connexion.cpp
*/

#include "Connection.hpp"

ClientConnection::ClientConnection(const std::string& serverIp, const std::string& serverPort)
    : ip_(serverIp), port_(serverPort), socket_(ioService) // Initialisez socket_ ici
{
    try {
        boost::asio::ip::tcp::resolver resolver(ioService);
        boost::asio::ip::tcp::resolver::query query(serverIp, serverPort);
        boost::asio::ip::tcp::resolver::iterator endpointIterator = resolver.resolve(query);

        boost::asio::connect(socket_, endpointIterator); // Utilisez socket_ ici

    } catch (const std::exception& e) {
        // Gérez l'exception ici, par exemple, en lançant une exception personnalisée
        std::cerr << e.what() << std::endl;
        // throw Error::Except("Connection\nConnection/Connection.cpp\nLine 18");
    }
}

bool ClientConnection::sendMessage(const std::string& msg)
{
    try {
        boost::asio::write(socket_, boost::asio::buffer(msg));
    } catch (const std::exception& e) {
        // Gérez l'exception ici, par exemple, en lançant une exception personnalisée
        // throw Error::Except("Send Message\nConnection/Connection.cpp\nLine 29");
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

bool ClientConnection::readMessage(const std::string& message)
{
    try {
        char buffer[1024];
        size_t size = socket_.read_some(boost::asio::buffer(buffer, sizeof(buffer)));
        std::string response(buffer, buffer + size);
        std::cout << "Reponse serveur => " << response << std::endl;
    } catch (const std::exception& e) {
        // throw Error::Except("Send Message\nConnection/Connection.cpp\nLine 29");
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}