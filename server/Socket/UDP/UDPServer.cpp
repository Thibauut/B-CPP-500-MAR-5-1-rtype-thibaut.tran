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

UDPServer::UDPServer(boost::asio::io_context& io_context, unsigned short port, std::shared_ptr<EntityManager> entity_manager)
    : socket_(io_context, udp::endpoint(udp::v4(), port)), entityManagerPtr_(entity_manager) {
        port_ = port;
        remote_endpoints_.clear();
        send_thread_ = std::thread(&UDPServer::sendThread, this);
        // send_thread_.join();
        StartReceive();
}

void UDPServer::StartReceive() {
    while (1) {
        recv_buf_ = {0};
        socket_.receive_from(boost::asio::buffer(recv_buf_), client);
        // std::cout << recv_buf_.data() << std::endl;
        handleReceive(recv_buf_.data());

        //     break;
        // if (remote_endpoints_.empty() == false)
        //     sendAll("test");
    }
}


void UDPServer::handleReceive(const std::string& message) {
    std::cout << "    <- " << message << std::endl;
    sendToClient("bien recu", client);
    if (EndpointExist(client) == false) {
        std::cout << "Endpoint not exist" << std::endl;
        remote_endpoints_.push_back(client);
    }
}

void UDPServer::sendToClient(const std::string& message, udp::endpoint &client_t)
{
    std::string new_message = message + "\n";
    std::cout << "    -> " << new_message;;
    socket_.send_to(boost::asio::buffer(new_message), client_t);
//         socket_.async_send_to(
//         boost::asio::buffer(message), client_t,
//         [this](const boost::system::error_code& error, std::size_t bytes_sent) {
//             if (error) {
//                 std::cerr << "Send error: " << error.message() << std::endl;
//                 // Entitys().get()->getEntity(1).get()->getComponentByType<Position>(1).get()->getPosition().first;
//             }
//         });
}

void UDPServer::sendAll(const std::string& message, std::vector<udp::endpoint> &endpoints)
{
    std::string new_message = message + "\n";
    for (udp::endpoint &remote_client : endpoints) {
        socket_.send_to(boost::asio::buffer(new_message), remote_client);
        std::cout << "    -> " << new_message;
    }
}

void UDPServer::sendThread() {
    while(1) {
        sleep(1);
        // toute les données a envoyer :
        sendAll("infos globales", remote_endpoints_);
    }
}

void UDPServer::moveLeft(int id, udp::endpoint &client) {
    entityManagerPtr_.get()->getEntity(id).get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->setPositionX(entityManagerPtr_.get()->getEntity(id).get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPositionX() - 2);
    std::string resp;
    resp = cmd_[0] + " " + player_x + " " + player_y;
}

void UDPServer::moveRight(int id, udp::endpoint &client)
{
    entityManagerPtr_.get()->getEntity(id).get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->setPositionX(entityManagerPtr_.get()->getEntity(id).get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPositionX() + 2);
    std::string resp;
    resp = cmd_[0] + " " + player_x + " " + player_y;
}

void UDPServer::moveUp(int id, udp::endpoint &client)
{
    entityManagerPtr_.get()->getEntity(id).get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->setPositionY(entityManagerPtr_.get()->getEntity(id).get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPositionY() - 2);
    std::string resp;
    resp = cmd_[0] + " " + player_x + " " + player_y;
}
void UDPServer::moveDown(int id, udp::endpoint &client)
{
    entityManagerPtr_.get()->getEntity(id).get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->setPositionY(entityManagerPtr_.get()->getEntity(id).get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPositionY() + 2);
    std::string resp;
    resp = cmd_[0] + " " + player_x + " " + player_y;
    sendToClient(resp, client);
}
void UDPServer::Shoot()
{
    std::string resp;
    // si l'arme peut re-tirer OK sinon KO
    // if ()
    //     resp = cmd_[0] + " \"SHOOT\" " + "\"OK\"";
    // else 
    //     resp = cmd_[0] + " \"SHOOT\" " + "\"KO\"";
    // sendToClient(resp);
}

#define player_id1 std::to_string(player.get()->getId())
#define player_x1 std::to_string(player.get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPosition().first)
#define player_y1 std::to_string(player.get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPosition().second)

// void UDPServer::sendPlayersPosition()
// {
//     std::string resp = "";
//     if (!entityManagerPtr_.get()->getEntitiesByType(player_type).empty()) {
//         for (std::shared_ptr<GameEngine::Entity> player : entityManagerPtr_.get()->getEntitiesByType(player_type)) {
//             resp = resp + player_id1 + " " + player_x1 + " " + player_y1;
//             if (player != entityManagerPtr_.get()->getEntitiesByType(player_type).back())
//                 resp = resp + " ";
//         }
//     }
//     else
//     std::cout << "Players list is empty :(" << std::endl;
//     sendAll(resp);
// }

// void UDPServer::sendProjectilsPosition(){StartSend("Projectil");}
// void UDPServer::sendBotsPosition(){ StartSend("Pnj");}
// void UDPServer::sendPowerUpPosition(){StartSend("Collectible");}
// void UDPServer::sendScores(){StartSend("Scores");}
void UDPServer::StartExec(const std::string& message, udp::endpoint &client) {
    ParsCmd(cmd_, message);
    if (!cmd_.empty()) {
        if (cmd_.size() > 1) {
            if (cmd_[1].compare("UP") == 0)
                moveUp(std::stoi(cmd_[0]), client);
            else if (cmd_[1].compare("DOWN") == 0)
                moveDown(std::stoi(cmd_[0]), client);
            else if (cmd_[1].compare("LEFT") == 0)
                moveLeft(std::stoi(cmd_[0]), client);
            else if (cmd_[1].compare("RIGHT") == 0)
                moveRight(std::stoi(cmd_[0]), client);
            else if (cmd_[1].compare("SHOOT") == 0)
                Shoot();
        }
        // else if (cmd_[0].compare("GETPLAYERS") == 0)
        //     sendPlayersPosition();
        // else if (cmd_[0].compare("GETPROJECTILES") == 0)
        //     sendProjectilsPosition();
        // else if (cmd_[0].compare("GETPNJ") == 0)
        //     sendBotsPosition();
        // else if (cmd_[0].compare("GETCOLLECTIBLES") == 0)
        //     sendPowerUpPosition();
        // else if (cmd_[0].compare("GETSCORES") == 0)
        //     sendScores();
        cmd_.clear();

    }

}

// int main()
// {
// 	boost::asio::io_service io_service;
// 	UDPServer server(io_service, 1234);
// 	io_service.run();
// 	return 0;
// }