/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** udpTest.cpp
*/

#include "UDPServer.hpp"

void ParsCmd(std::vector<std::string> &tmp, std::string cmd)
{
    int i = 0;
    std::string first_arg;
    for (char &c : cmd) {
        if (c == ' ' || c == '\0') {
            i++;
            tmp.push_back(first_arg);
            break;
        }
        first_arg.push_back(c);
        i++;
    }
    std::string arg;
    for (int start_stock = 0 ;cmd[i] != '\0'; i++) {
        if (cmd[i] == '"')
            start_stock++, i++;
        if (start_stock == 1)
            arg.push_back(cmd[i]);
        if (start_stock == 2) {
            tmp.push_back(arg);
            arg.clear();
            start_stock = 0;
        }
    }
}

UDPServer::UDPServer(boost::asio::io_service& io_service, unsigned short port, std::shared_ptr<EntityManager> entity_manager)
    : socket_(io_service, udp::endpoint(udp::v4(), port)), entityManagerPtr_(entity_manager) {
        recv_buf_.resize(1024);
        StartReceive();
}

void UDPServer::StartReceive() {
    socket_.async_receive_from(
    boost::asio::buffer(recv_buf_), remote_endpoint_,
    [this](const boost::system::error_code& error, std::size_t bytes_received) {
        if (!error || error == boost::asio::error::message_size) {
            std::string message(recv_buf_.begin(), recv_buf_.begin() + bytes_received);
            StartExec(message);
            StartReceive();
        } else {
            std::cerr << "Receive error: " << error.message() << std::endl;
        }
    });
}

void UDPServer::StartSend(const std::string& message){
    socket_.async_send_to(
        boost::asio::buffer(message), remote_endpoint_,
        [this](const boost::system::error_code& error, std::size_t bytes_sent) {
            if (error) {
                std::cerr << "Send error: " << error.message() << std::endl;
                // Entitys().get()->getEntity(1).get()->getComponentByType<Position>(1).get()->getPosition().first;
            }
        });
}

void UDPServer::moveLeft() {
    
    StartSend("Left");
    
}

void UDPServer::moveRight(){StartSend("Right");}
void UDPServer::moveUp(){StartSend("Up");}
void UDPServer::moveDown(){StartSend("Down");}

void UDPServer::SendAllPlayersPosition(){StartSend("Player");}
void UDPServer::SendAllProjectilsPosition(){StartSend("Projectil");}
void UDPServer::SendAllPnjPosition(){StartSend("Pnj");}
void UDPServer::SendAllCollectiblesPosition(){StartSend("Collectible");}
void UDPServer::Shoot(){StartSend("Shoot");}
void UDPServer::sendScores(){StartSend("Scores");}
void UDPServer::StartExec(const std::string& message) {

    ParsCmd(cmd_, message);
    if (!cmd_.empty()){
        if (cmd_[1].compare("UP") == 0)
            moveUp();
        else if (cmd_[1].compare("DOWN") == 0)
            moveDown();
        else if (cmd_[1].compare("LEFT") == 0)
            moveLeft();
        else if (cmd_[1].compare("RIGHT") == 0)
            moveRight();
        else if (cmd_[1].compare("SHOOT") == 0)
            Shoot();
        else if (cmd_[1].compare("GETPLAYERS") == 0)
            SendAllPlayersPosition();
        else if (cmd_[1].compare("GETPROJECTILES") == 0)
            SendAllProjectilsPosition();
        else if (cmd_[1].compare("GETPNJ") == 0)
            SendAllPnjPosition();
        else if (cmd_[1].compare("GETCOLLECTIBLES") == 0)
            SendAllCollectiblesPosition();
        else if (cmd_[1].compare("GETSCORES") == 0)
            sendScores();
        else {
            StartSend("Unknow Cmd");
        }
        cmd_.clear();

    }
    else {
        std::cout << "Cmd is empty..." << std::endl;
        StartSend("Invalide Syntax");
    }

}

// int main()
// {
// 	boost::asio::io_service io_service;
// 	UDPServer server(io_service, 1234);
// 	io_service.run();
// 	return 0;
// }