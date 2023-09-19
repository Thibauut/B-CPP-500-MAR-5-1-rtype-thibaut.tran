/*
** EPITECH PROJECT, 2023
** Client
** File description:
** Client
*/

#include "Connexion.hpp"

using boost::asio::ip::tcp;

void tcp_client(const std::string& serverIp, const std::string& serverPort)
{
    try {
        boost::asio::io_service ioService;
        tcp::resolver resolver(ioService);
        tcp::resolver::query query(serverIp, serverPort);
        tcp::resolver::iterator endpointIterator = resolver.resolve(query);

        tcp::socket socket(ioService);
        boost::asio::connect(socket, endpointIterator);

        std::string Message = "Dis a raph il arrête de choup\n";
        boost::asio::write(socket, boost::asio::buffer(Message));

        char buffer[1024];
        size_t size = socket.read_some();
    } catch (std::exception& e) {
        throw Error::Except(e.what());
    }
}