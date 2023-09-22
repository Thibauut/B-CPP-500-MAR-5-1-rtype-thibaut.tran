/*
** EPITECH PROJECT, 2023
** Client
** File description:
** Connexion.cpp
*/

#include "ConnectionTCP.hpp"

std::atomic<bool> shouldExit(false);

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
    }
}

bool ClientConnectionTCP::sendMessage(const std::string& msg)
{
    if (!socket_.is_open()) {
        std::cerr << "La connexion au serveur n'est pas établie." << std::endl;
        return false;
    }
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

void ClientConnectionTCP::handleRead(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    std::cout << "handleRead" << std::endl;
    if (!error) {
        const char* dataBegin = boost::asio::buffer_cast<const char*>(buffer_.data());
        const char* dataEnd = dataBegin + bytes_transferred;
        std::string responseData(dataBegin, dataEnd);
        readMessage();
    } else {
        std::cerr << "Erreur lors de la lecture du message : " << error.message() << std::endl;
    }
}

void ClientConnectionTCP::readMessage()
{
    std::cout << "readMessage" << std::endl;

    boost::asio::read_until(socket_, buffer_, '\n');

    std::istream response_stream(&buffer_);
    std::string server_response;
    std::getline(response_stream, server_response);
    response_ = server_response;

    std::cout << "Réponse lue : " << server_response << std::endl;
}

void ClientConnectionTCP::run()
{
    if (!socket_.is_open()) {
        std::cerr << "La connexion au serveur a échoué." << std::endl;
        return;
    }
    std::thread readThread([this]() {
        std::cout << "dans le thread" << std::endl;
        while (!shouldExit) {
            readMessage();
            std::cout << response_ << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    });
    readThread.join();
}

std::string ClientConnectionTCP::extractArguments(const std::string&input, const std::string& keyword) {
    const std::string loginKeyword = keyword;
    size_t loginPos = input.find(loginKeyword);

    if (loginPos != std::string::npos) {
        return input.substr(loginPos + loginKeyword.length());
    } else {
        return "";
    }
}

void ClientConnectionTCP::Login()
{
    setMessage("LOGIN \"" + username_ + "\"\n");
    sendMessage(message_);
    message_ = "";
    readMessage();
    readMessage();

    std::cout << "Réponse from login : " << response_ << std::endl;

    uuid_ = extractArguments(response_, "LOGIN ");

    std::cout << "UUID : " << uuid_ << std::endl;
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
