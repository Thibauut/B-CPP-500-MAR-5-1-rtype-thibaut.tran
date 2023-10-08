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

UDPServer::UDPServer(boost::asio::io_context& io_context, unsigned short port, std::shared_ptr<EntityManager> entity_manager)
    : socket_(io_context, udp::endpoint(udp::v4(), port)), entityManagerPtr_(entity_manager) {
        port_ = port;
        remote_endpoints_.clear();
        send_thread_ = std::thread(&UDPServer::sendThread, this);
        StartReceive();
}

void UDPServer::StartReceive() {
    for (;;) {
        recv_buf_ = {0};
        size_t size = socket_.receive_from(boost::asio::buffer(recv_buf_), client);
        handleReceive(deserialize(std::string(recv_buf_.data(), size)));
        sendPlayersPosition();
        //     break;
        // if (remote_endpoints_.empty() == false)
        //     sendAll("test");
    }
}

void UDPServer::handleReceive(Entity entity) {
    StartExec(entity, client);
    if (EndpointExist(client) == false) {
        remote_endpoints_.push_back(std::make_shared<udp::endpoint>(client));
    }
}

void UDPServer::sendToClient(const std::string& message, udp::endpoint &client_t)
{
    std::string new_message = message + "\n";
    // std::cout << "    -> " << new_message;;
    socket_.send_to(boost::asio::buffer(new_message), client_t);

}

void UDPServer::sendAll(const std::string& message, std::vector<std::shared_ptr<udp::endpoint>> &endpoints)
{
    for (std::shared_ptr<udp::endpoint> remote_client : endpoints) {
        socket_.send_to(boost::asio::buffer(message), *remote_client.get());
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
    if (!Entities().get()->getEntitiesByType(bullet_type).empty()) {
        for (std::shared_ptr<GameEngine::Entity> bullet : entityManagerPtr_.get()->getEntitiesByType(bullet_type)) {
            sendAll(serialize(bullet), remote_endpoints_);
        }
    }
}

void UDPServer::setPlayerPosition(Entity &player)
{
    entityManagerPtr_->getEntity(player.getId())->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->setPosition(
        player.getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPositionX(),
        player.getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPositionY());
}

void UDPServer::setMobPosition(Entity player)
{
    entityManagerPtr_->getEntity(player.getId())->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->setPosition(
        player.getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPositionX(),
        player.getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPositionY());
}

void UDPServer::StartExec(Entity &entity, udp::endpoint &client) {
        if (entity.getType() == 1)
            setPlayerPosition(entity);
}