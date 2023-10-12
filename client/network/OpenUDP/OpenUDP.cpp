/*
** EPITECH PROJECT, 2023
** Client
** File description:
** Connexion.cpp
*/

    #include <boost/serialization/vector.hpp>
    #include <boost/serialization/shared_ptr.hpp>
    #include <boost/archive/binary_oarchive.hpp>
    #include <boost/archive/binary_iarchive.hpp>
    #include <boost/serialization/export.hpp>
#include "OpenUDP.hpp"
#include "../../include/global.hpp"
#include <future>

ClientOpenUDP::ClientOpenUDP(const std::string& serverIp, const std::string& serverPort, std::shared_ptr<EntityManager> &entities, const std::string my_id)
    : udpAddress_(serverIp), udpPort_(serverPort), socket_(ioService), my_id_(my_id), entities_(entities)
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

void ClientOpenUDP::sendMessageSync(const std::string& msg)
{
    socket_.send_to(boost::asio::buffer(msg), endpoint_);
    return;
}

std::string ClientOpenUDP::serialize(std::shared_ptr<Entity> entity) {
    std::ostringstream oss;
    boost::archive::binary_oarchive archive(oss);
    archive << *entity.get();
    return oss.str();
}

Entity ClientOpenUDP::deserialize(std::string serializedData) {
    std::istringstream received_data(serializedData);
    boost::archive::binary_iarchive ia(received_data);
    Entity received_obj(971);
    ia >> received_obj;
    return received_obj;
}

void ClientOpenUDP::readMessageGlobal()
{
    std::array<char, 1024> buffer;
    boost::asio::ip::udp::endpoint senderEndpoint;
    size_t size = socket_.receive_from(boost::asio::buffer(buffer), senderEndpoint);

    std::shared_ptr<Entity> ent = std::make_shared<Entity>(deserialize(std::string(buffer.data(), size)));
    if (ent == nullptr)
        return;

    for (std::shared_ptr<Entity> &entity: entities_->getEntities()) {
        if (entity->getId() == ent->getId()) {
            entity->getComponentByType<Position>(CONFIG::CompType::POSITION)->setPositionX(ent->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionX());
            entity->getComponentByType<Position>(CONFIG::CompType::POSITION)->setPositionY(ent->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionY());
            entity->getComponentByType<Sprite>(CONFIG::CompType::SPRITE)->setPositionSprite(sf::Vector2f(ent->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionX(), ent->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionY()));
            return;
        }
    }

    if (ent->getId() != std::stoi(my_id_)) {
        entities_->createEntity();
        std::shared_ptr<Sprite> spriteComp = ent->getComponentByType<Sprite>(CONFIG::CompType::SPRITE);
        if (spriteComp) {
            spriteComp->initSprite();
        }
        entities_->addEntity(*ent.get());
    }

    return;
}

void ClientOpenUDP::setMessage(const std::string& message)
{
    message_ = message;
}

bool ClientOpenUDP::getRunning()
{
    return running_;
}

void ClientOpenUDP::recursRead(std::shared_ptr<Entity> &player) {
    std::array<char, 1024> buffer;
    boost::asio::ip::udp::endpoint senderEndpoint;
    size_t size = socket_.receive_from(boost::asio::buffer(buffer), senderEndpoint);
    std::shared_ptr<Entity> ent = std::make_shared<Entity>(deserialize(std::string(buffer.data(), size)));
    if (ent == nullptr)
        recursRead(player);
    else {
        player = ent;
    }
}

void ClientOpenUDP::init(std::shared_ptr<Entity> &player) {
    sendMessageSync("LOGIN " + my_id_ + "\n");
    recursRead(player);
}

void ClientOpenUDP::run() {
    for (;;)
        readMessageGlobal();
    ioService.stop();
}