/*
** EPITECH PROJECT, 2023
** Client
** File description:
** Connexion.cpp
*/

#include "ConnectionTCP.hpp"

ClientConnectionTCP::ClientConnectionTCP(const std::string& userName, const std::string& serverIp, const std::string& serverPort)
    : ip_(serverIp),  port_(serverPort), username_(userName), socket_(ioService)
{
    try {
        boost::asio::ip::tcp::resolver resolver(ioService);
        boost::asio::ip::tcp::resolver::query query(serverIp, serverPort);
        boost::asio::ip::tcp::resolver::iterator endpointIterator = resolver.resolve(query);

        boost::asio::connect(socket_, endpointIterator);

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        // throw Error::Except("Connection\nConnection/Connection.cpp\nLine 18");
    }
}

bool ClientConnectionTCP::sendMessage(const std::string& msg)
{
    std::vector<boost::asio::const_buffer> buffers;
    buffers.push_back(boost::asio::buffer(msg));

    boost::asio::async_write(socket_, buffers,
        [](const boost::system::error_code& error, std::size_t /*bytes_transferred*/) {
            if (!error) {
                std::cout << "Message envoyé avec succès" << std::endl;
            } else {
                std::cerr << "Erreur lors de l'envoi du message : " << error.message() << std::endl;
            }
        });
    return true;
}

std::string ClientConnectionTCP::readMessage()
{
    if (!socket_.is_open()) {
        std::cerr << "La connexion au serveur n'est pas établie." << std::endl;
        return NULL;
    }
    boost::asio::streambuf response_buffer;
    //________//
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("192.168.0.30"), 12345);
    boost::asio::ip::tcp::socket& socket = getSocket();
    boost::array<char, 128> buf;
    boost::system::error_code error;
    int len = socket.read_some(boost::asio::buffer(buf), error);
    if (error == boost::asio::error::eof) {
            std::cout << "\nTerminé !" << std::endl;
        }
    std::string serveurResponse(buf.data(), len);
    std::cout << "Serveur Response => " << serveurResponse << std::endl;
    return serveurResponse;
}

void ClientConnectionTCP::run()
{
    // bool login = false;
    // while (running_) {
        // readMessage();
        // readMessage();
        // std::this_thread::sleep_for(std::chrono::seconds(1));
        // Login();
        // std::this_thread::sleep_for(std::chrono::seconds(1));
        // if (!login) {
            // login = true;
        // }
    // }
}

void ClientConnectionTCP::Login()
{
        setMessage("LOGIN \"" + username_ + "\"");
        sendMessage(message_);
        readMessage();
        std::string loginInfo = readMessage();
        size_t delimiterPos = loginInfo.find(' ');
        if (delimiterPos != std::string::npos) {
            std::string cmd = loginInfo.substr(0, delimiterPos);
            std::string arg = loginInfo.substr(delimiterPos + 1);
            uuid_ = arg;
            std::cout << "uuid stocked -> " << '\'' << uuid_  << '\'' << std::endl;
        } else {

        }
}

void ClientConnectionTCP::setMessage(const std::string& message)
{
    message_ = message;
}

boost::asio::ip::tcp::socket& ClientConnectionTCP::getSocket()
{
    return socket_;
}

boost::asio::io_service& ClientConnectionTCP::getService()
{
    return ioService;
}

bool ClientConnectionTCP::getRunning() {
    return this->running_;
}