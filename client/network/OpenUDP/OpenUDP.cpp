/*
** EPITECH PROJECT, 2023
** Client
** File description:
** Connexion.cpp
*/

#include "OpenUDP.hpp"
#include "../../include/global.hpp"
#include <future>

ClientOpenUDP::ClientOpenUDP(const std::string& serverIp, const std::string& serverPort, std::vector<std::shared_ptr<PlayerUDP>>& players, const std::string my_id)
    : udpAddress_(serverIp), udpPort_(serverPort), socket_(ioService), players_(players), my_id_(my_id)
{
    try {
        boost::asio::ip::address ip_address = boost::asio::ip::address::from_string(udpAddress_);
        boost::asio::ip::udp::endpoint endpoint(ip_address, std::stoi(udpPort_));
        endpoint_ = endpoint;
        socket_.open(boost::asio::ip::udp::v4());
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

bool ClientOpenUDP::sendMessageSync(const std::string& msg)
{
    std::cout << "Message envoyé => " << msg << std::endl;
    socket_.send_to(boost::asio::buffer(msg), endpoint_);
    // readMessage();
    return true;
}

bool ClientOpenUDP::sendMessageSyncFirst(const std::string& msg)
{
    // std::cout << "Message envoyé => " << msg << std::endl;
    socket_.send_to(boost::asio::buffer(msg), endpoint_);
    // readPositionFirst();
    return true;
}

bool ClientOpenUDP::getPLayersPos(const std::string& msg)
{
    socket_.send_to(boost::asio::buffer(msg), endpoint_);
    readPos();
    return true;
}

bool ClientOpenUDP::readPos()
{
    boost::array<char, 1024> buffer;
    boost::asio::ip::udp::endpoint senderEndpoint;
    boost::system::error_code ec;
    socket_.receive_from(boost::asio::buffer(buffer), senderEndpoint);
    std::istringstream iss(buffer.data());
    int id, posX, posY;
    if (iss >> id >> posX >> posY) {
        for (std::shared_ptr<PlayerUDP> &pl : players_) {
            if (pl.get()->_id != id) {
                pl.get()->_x = posX;
                pl.get()->_y = posY;
                pl.get()->_sprite.setPosition(sf::Vector2f(pl->_x, pl->_y));
            }
        }
    } else {
        std::cerr << "Erreur de parsing." << std::endl;
    }
    return true;
}

bool ClientOpenUDP::readPositionFirst()
{
    bool success = false;

        boost::array<char, 1024> buffer;
        boost::asio::ip::udp::endpoint senderEndpoint;
        boost::system::error_code ec;
        socket_.receive_from(boost::asio::buffer(buffer), senderEndpoint);
        // std::cout << "Reponse serveur => " << buffer.data() << std::endl;
        std::istringstream iss(buffer.data());
        int id, posX, posY;
        while (iss >> id >> posX >> posY) {
            std::shared_ptr<PlayerUDP> player = std::make_shared<PlayerUDP>(id, posX, posY);
            players_.push_back(player);
        }
        for (std::shared_ptr<PlayerUDP> &pl : players_) {
            pl.get()->_sprite.setPosition(sf::Vector2f(pl->_x, pl->_y));
        }
        success = true;
        if (ec || buffer.empty()) {
            success = false;
        }
    return success;
}

bool ClientOpenUDP::readMessage()
{
    bool success = false;

        boost::array<char, 1024> buffer;
        boost::asio::ip::udp::endpoint senderEndpoint;
        boost::system::error_code ec;
        socket_.receive_from(boost::asio::buffer(buffer), senderEndpoint);
        std::cout << "Reponse serveur => " << buffer.data() << std::endl;
        std::istringstream iss(buffer.data());
        int id, posX, posY;
        if (iss >> id >> posX >> posY) {
            for (std::shared_ptr<PlayerUDP> &pl : players_) {
                if (pl.get()->_id == id) {
                    pl.get()->_x = posX;
                    pl.get()->_y = posY;
                    pl.get()->_sprite.setPosition(sf::Vector2f(pl->_x, pl->_y));
                }
            }
            success = true;
        } else {
            std::cerr << "Erreur de parsing." << std::endl;
        }
        if (ec || buffer.empty()) {
            success = false;
        }

    return success;
}

void ClientOpenUDP::setMessage(const std::string& message)
{
    message_ = message;
}

bool ClientOpenUDP::getRunning()
{
    return running_;
}

void ClientOpenUDP::run() {
    std::cout << "OpenUDP running" << std::endl;
    message_ = "Hello from OpenUDP\n";
    running_ = true;

    std::thread ioThread([&] {
        ioService.run();
    });

    int index = 0;
    while (running_) {
        index = 0;
        if (action) {
            if (*action == UP) {
                for (std::shared_ptr<PlayerUDP> &player : players_) {
                    if (player.get()->_id == std::stoi(my_id_)) {
                        sendMessageSync(my_id_ + " " + std::to_string(player.get()->_x) + " " + std::to_string(player.get()->_y -= 1) + " false");
                    }
                }
            }
            if (*action == DOWN) {
                for (std::shared_ptr<PlayerUDP> &player : players_) {
                    if (player.get()->_id == std::stoi(my_id_)) {
                        sendMessageSync(my_id_ + " " + std::to_string(player.get()->_x) + " " + std::to_string(player.get()->_y += 1) + " false");
                    }
                }
            }
            if (*action == LEFT) {
                for (std::shared_ptr<PlayerUDP> &player : players_) {
                    if (player.get()->_id == std::stoi(my_id_)) {
                        sendMessageSync(my_id_ + " " + std::to_string(player.get()->_x -= 1) + " " + std::to_string(player.get()->_y) + " false");
                    }
                }
            }
            if (*action == RIGHT) {
                for (std::shared_ptr<PlayerUDP> &player : players_) {
                    if (player.get()->_id == std::stoi(my_id_)) {
                        sendMessageSync(my_id_ + " " + std::to_string(player.get()->_x += 1) + " " + std::to_string(player.get()->_y) + " false");
                    }
                }
            }
            if (*action == SHOOT) {
                for (std::shared_ptr<PlayerUDP> &player : players_) {
                    if (player.get()->_id == std::stoi(my_id_)) {
                        sendMessageSync(my_id_ + " " + std::to_string(player.get()->_x) + " " + std::to_string(player.get()->_y) + " true");
                    }
                }
            }
            // if (*action == DOWN) {
            //     sendMessageSync(my_id_ + " DOWN");
            // }
            // if (*action == LEFT) {
            //     sendMessageSync(my_id_ + " LEFT");
            // }
            // if (*action == RIGHT) {
            //     sendMessageSync(my_id_ + " RIGHT");
            // }
            // if (*action == SHOOT) {
            //     sendMessageSync(my_id_ + " SHOOT");
            // }
            action = nullptr;
        }
        // getPLayersPos("GETPLAYERS"); //info all players
        // boost::array<char, 1024> buffer;
        // boost::asio::ip::udp::endpoint senderEndpoint;
        // boost::system::error_code ec;
        // socket_.receive_from(boost::asio::buffer(buffer), senderEndpoint);
        // std::cout << "Reponse serveur => " << buffer.data() << std::endl;

    }

    ioService.stop();
    ioThread.join();
}