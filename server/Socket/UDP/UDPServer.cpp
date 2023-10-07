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
#define bullet_type 3

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
    // std::cout << "    <- " << message << std::endl;
    StartExec(message, client);
    if (EndpointExist(client) == false) {
        remote_endpoints_.push_back(std::make_shared<udp::endpoint>(client));
    }
}

void UDPServer::sendToClient(const std::string& message, udp::endpoint &client_t)
{
    std::string new_message = message + "\n";
    // std::cout << "    -> " << new_message;;
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

void UDPServer::sendAll(const std::string& message, std::vector<std::shared_ptr<udp::endpoint>> &endpoints)
{
    for (std::shared_ptr<udp::endpoint> remote_client : endpoints) {
        socket_.send_to(boost::asio::buffer(message), *remote_client.get());
        // std::cout << "    -> " << new_message;
    }
}

void UDPServer::sendThread() {
    while(1) {
        sendPlayersPosition();
    }
}

#define player_id1 std::to_string(player.get()->getId())
#define player_x1 std::to_string(player.get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPosition().first)
#define player_y1 std::to_string(player.get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPosition().second)

void UDPServer::sendPlayersPosition()
{
    std::string resp = "";
    if (!Entities().get()->getEntitiesByType(player_type).empty()) {
        for (std::shared_ptr<GameEngine::Entity> player : entityManagerPtr_.get()->getEntitiesByType(player_type)) {
            serialize(player);
                sendAll(serialize(player), remote_endpoints_);
        }
    }
    else
        std::cout << "Players list is empty :(" << std::endl;
}
#define bullet_id std::to_string(bullet.get()->getId())
#define bullet_x std::to_string(bullet.get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPosition().first)
#define bullet_y std::to_string(bullet.get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPosition().second)

void UDPServer::sendBulletPosition()
{
    std::string resp = "";
    if (!Entities().get()->getEntitiesByType(bullet_type).empty()) {
        for (std::shared_ptr<GameEngine::Entity> bullet : entityManagerPtr_.get()->getEntitiesByType(bullet_type)) {
            std::cout << "serialized data:" << serialize(bullet);
            resp = resp + bullet_id + " " + bullet_x + " " + bullet_y;
            if (bullet != entityManagerPtr_.get()->getEntitiesByType(bullet_type).back())
                resp = resp + " ";
        }
        sendAll(resp, remote_endpoints_);
    }
    else
        std::cout << "Players list is empty :(" << std::endl;
}

void UDPServer::setPlayerStatus(int id, int x, int y, std::string shoot)
{
    entityManagerPtr_->getEntity(id)->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->setPosition(x, y);
}
void UDPServer::StartExec(const std::string& message, udp::endpoint &client) {
    ParsCmd(cmd_, message);
    if (!cmd_.empty()) {
        if (cmd_.size() > 1) {
            setPlayerStatus(std::atoi(cmd_.at(0).c_str()), std::atoi(cmd_.at(1).c_str()),  std::atoi(cmd_.at(2).c_str()), cmd_.at(3));
        }
        cmd_.clear();

    }

}