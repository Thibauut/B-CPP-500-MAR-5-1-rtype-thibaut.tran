/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** udpTest.cpp
*/

#include "UDPServer.hpp"
#define player_x  std::to_string(entityManagerPtr_.get()->getEntity(std::stoi(cmd_[0])).get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPosition().first)
#define player_y  std::to_string(entityManagerPtr_.get()->getEntity(std::stoi(cmd_[0])).get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPosition().second)
#define player_type 1

void ParsCmd(std::vector<std::string> &tmp, std::string cmd)
{
    int i = 0;
    std::istringstream iss(cmd);
    std::string arg;
    while (iss >> arg) {
        tmp.push_back(arg);
    }
}

UDPServer::UDPServer(boost::asio::io_service& io_service, unsigned short port, std::shared_ptr<EntityManager> entity_manager)
    : socket_(io_service, udp::endpoint(udp::v4(), port)), entityManagerPtr_(entity_manager) {
        recv_buf_.resize(1024);
        StartReceive();
}

void UDPServer::StartReceive() {
    std::size_t size = socket_.receive_from(boost::asio::buffer(recv_buf_), remote_endpoint_);
    std::string message(recv_buf_.begin(), recv_buf_.begin() + size);
    std::cout << "    <- " << message << std::endl;
    StartExec(message);
    StartReceive();
}

void UDPServer::StartSend(const std::string& message)
{
    std::string new_message = message + "\n";
    std::cout << "    -> " << new_message;;
    socket_.send_to(boost::asio::buffer(new_message), remote_endpoint_);
}

void UDPServer::moveLeft() {
    std::string resp;
    resp = cmd_[0] + " " + player_x + " " + player_y;
    StartSend(resp);
}

void UDPServer::moveRight()
{
    std::string resp;
    resp = cmd_[0] + " " + player_x + " " + player_y;
    StartSend(resp);
}
void UDPServer::moveUp()
{
    std::string resp;
    resp = cmd_[0] + " " + player_x + " " + player_y;
    StartSend(resp);
}
void UDPServer::moveDown()
{
    std::string resp;
    resp = cmd_[0] + " " + player_x + " " + player_y;
    StartSend(resp);
}
void UDPServer::Shoot()
{
    std::string resp;
    // si l'arme peut re-tirer OK sinon KO
    // if ()
    //     resp = cmd_[0] + " \"SHOOT\" " + "\"OK\"";
    // else 
    //     resp = cmd_[0] + " \"SHOOT\" " + "\"KO\"";
    StartSend(resp);
}

#define player_id1 std::to_string(player.get()->getId())
#define player_x1 std::to_string(player.get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPosition().first)
#define player_y1 std::to_string(player.get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPosition().second)

void UDPServer::sendPlayersPosition()
{
    std::string resp = "";
    std::cout << "HERE !" << std::endl;
    if (!entityManagerPtr_.get()->getEntitiesByType(player_type).empty()) {
            std::cout << "EntityManager isn't empty" << std::endl;
        for (std::shared_ptr<GameEngine::Entity> player : entityManagerPtr_.get()->getEntitiesByType(player_type)) {
                std::cout << "In list progress..." << std::endl;
            std::cout << player_x1 << player_y1 << std::endl;
            resp = resp + player_id1 + " " + player_x1 + " " + player_y1;
            if (player != entityManagerPtr_.get()->getEntitiesByType(player_type).back())
                resp = resp + " ";
        }
    }
    else
    std::cout << "Players list is empty :(" << std::endl;
    StartSend(resp);
}

void UDPServer::sendProjectilsPosition(){StartSend("Projectil");}
void UDPServer::sendBotsPosition(){ StartSend("Pnj");}
void UDPServer::sendPowerUpPosition(){StartSend("Collectible");}
void UDPServer::sendScores(){StartSend("Scores");}
void UDPServer::StartExec(const std::string& message) {
    ParsCmd(cmd_, message);
    if (!cmd_.empty()) {
        if (cmd_.size() > 1) {
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
        }
        else if (cmd_[0].compare("GETPLAYERS") == 0)
            sendPlayersPosition();
        else if (cmd_[0].compare("GETPROJECTILES") == 0)
            sendProjectilsPosition();
        else if (cmd_[0].compare("GETPNJ") == 0)
            sendBotsPosition();
        else if (cmd_[0].compare("GETCOLLECTIBLES") == 0)
            sendPowerUpPosition();
        else if (cmd_[0].compare("GETSCORES") == 0)
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