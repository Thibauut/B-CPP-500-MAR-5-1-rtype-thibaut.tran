/*
** EPITECH PROJECT, 2023
** Client
** File description:
** Connexion.cpp
*/

#include "OpenUDP.hpp"

ClientOpenUDP::ClientOpenUDP(const std::string& udpAdress)
    : udpAddress_(udpAdress), socket_(ioService)

{
    try {
        size_t colonPos = udpAddress_.find(':');
        if (colonPos == std::string::npos) {
            // throw ERROR::MyException("Invalid UDP address format. Use 'ip:port'.\nOpen/Open.cpp\nLine 17");
            std::cerr << "Bad syntax" << std::endl;
            exit(-1);
        }
        std::string ip = udpAddress_.substr(0, colonPos);
        std::string portStr = udpAddress_.substr(colonPos + 1);
        unsigned short port = std::stoi(portStr);
        endpoint_ = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(ip), port);
        socket_.open(boost::asio::ip::udp::v4());
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        // throw Error::Except("Open\nOpen/Open.cpp\nLine 18");
    }
}

bool ClientOpenUDP::sendMessage(const std::string& msg)
{
    try {
        // Convertir la chaîne en une séquence de tampons boost::asio
        std::vector<boost::asio::const_buffer> buffers;
        buffers.push_back(boost::asio::buffer(msg));

        // Utiliser async_send_to avec la séquence de tampons
        socket_.async_send_to(buffers, endpoint_,
            [](const boost::system::error_code& error, std::size_t /*bytes_sent*/) {
                if (!error) {
                    std::cout << "fine" << std::endl;
                } else {
                    // Gérez l'erreur ici
                    std::cerr << "Erreur lors de l'envoi du message : " << error.message() << std::endl;
                }
            });
    } catch (const std::exception& e) {
        // Gérez l'exception ici
        std::cerr << e.what() << std::endl;
    }
    return true;
}

bool ClientOpenUDP::readMessage()
{
    // Allouez un tampon pour stocker le message reçu
    char buffer[1024];
    boost::asio::ip::udp::endpoint senderEndpoint;

    // Utilisez async_receive_from pour recevoir le message de manière asynchrone
    socket_.async_receive_from(boost::asio::buffer(buffer, sizeof(buffer)), senderEndpoint,
        [this, buffer](const boost::system::error_code& error, std::size_t size) {
            if (!error) {
                // Traitez le message reçu ici
                std::string response(buffer, buffer + size);
                std::cout << "Reponse serveur => " << response << std::endl;
            } else {
                // Gérez l'erreur ici
                std::cerr << "Erreur lors de la réception du message : " << error.message() << std::endl;
            }

            // Continuez à lire les messages de manière asynchrone
            readMessage();
        });
    return true;
}

void ClientOpenUDP::setMessage(const std::string& message)
{
    message_ = message;
}

void ClientOpenUDP::run() {
    while (running_) {
        readMessage();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        sendMessage(message_);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}