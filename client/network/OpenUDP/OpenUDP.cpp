/*
** EPITECH PROJECT, 2023
** Client
** File description:
** Connexion.cpp
*/

#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/unique_ptr.hpp>
#include <boost/serialization/array.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/asio.hpp>
#include "OpenUDP.hpp"
#include <future>

ClientOpenUDP::ClientOpenUDP(const std::string& serverIp, const std::string& serverPort, std::shared_ptr<EntityManager> &entities, const std::string my_id , std::string titleGame)
    : udpAddress_(serverIp), udpPort_(serverPort), socket_(ioService), my_id_(my_id), entities_(entities), _titleGame(titleGame)
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
    // std::cout << "serializedData: " << serializedData << std::endl;
    boost::archive::binary_iarchive ia(received_data);
    // std::cout << "HERE !!" << std::endl;
    Entity received_obj(971);
    // std::cout << "Maybe here !!" << std::endl;
    ia >> received_obj;
    // std::cout << "Or here !!" << std::endl;
    return received_obj;
}

void ClientOpenUDP::readMessageGlobal(unsigned int my_id)
{
    std::array<char, 1024> buffer;
    boost::asio::ip::udp::endpoint senderEndpoint;
    size_t size = socket_.receive_from(boost::asio::buffer(buffer), senderEndpoint);

    std::shared_ptr<Entity> ent = std::make_shared<Entity>(deserialize(std::string(buffer.data(), size)));
    if (!ent)
        return;

    //adding entities
    entities_->lock();
    for (std::shared_ptr<Entity> &entity: entities_->getEntities()) {
        if (entity->getUuid() == ent->getUuid() && ent->getIsDeath() == false && ent->getId() != my_id) {
            if (_titleGame == "¨PONG") {
                std::shared_ptr<Score> scoreComp = entity->getComponentByType<Score>(CONFIG::CompType::SCORE);
                std::shared_ptr<Score> newEntScore = ent->getComponentByType<Score>(CONFIG::CompType::SCORE);
                if (newEntScore == nullptr || scoreComp == nullptr) {
                    entities_->unlock();
                    return;
                }
                scoreComp->setScore(newEntScore->getScore());
            }
            std::shared_ptr<Sprite> spriteComp = entity->getComponentByType<Sprite>(CONFIG::CompType::SPRITE);
            std::shared_ptr<Position> positionComp = entity->getComponentByType<Position>(CONFIG::CompType::POSITION);
            std::shared_ptr<Cooldown> cooldownDeleteComp = entity->getComponentByType<Cooldown>(CONFIG::CompType::TIMECOMP);
            if (cooldownDeleteComp != nullptr) {
                cooldownDeleteComp->reset("delete");
            }
            if (spriteComp == nullptr || positionComp == nullptr) {
                entities_->unlock();
                return;
            }
            positionComp->setPositionX(ent->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionX());
            positionComp->setPositionY(ent->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionY());
            spriteComp->setPositionSprite(sf::Vector2f(positionComp->getPositionX(), positionComp->getPositionY()));
            entities_->unlock();
            return;
        }
         if (entity->getUuid() == ent->getUuid() && ent->getIsDeath() == true) {
            for (std::shared_ptr<Sprite> &spriteComp : entity->getComponentsByType<Sprite>(CONFIG::CompType::SPRITE)) {
                if (spriteComp->getSpriteType() == CONFIG::SpriteType::DEATHSPRITE && entity->getType() == 2)
                    spriteComp->setDoAnimationDead(true);
            }
            entity->setIsDeath(true);
            entities_->unlock();
            return;
        }
    }
    if (ent->getId() != std::stoi(my_id_)) {
        entities_->createEntity();
        std::vector<std::shared_ptr<Sprite>> spriteComps = ent->getComponentsByType<Sprite>(CONFIG::CompType::SPRITE);
        for (std::shared_ptr<Sprite> &spriteComp : spriteComps) {
            spriteComp->initSprite();
        }
        entities_->addEntity(*ent.get());
    }
    entities_->unlock();
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
    std::cout << "Ici la vida" << std::endl;
    if (ent == nullptr)
        recursRead(player);
    else {
        player = ent;
    }
}

void ClientOpenUDP::init(std::shared_ptr<Entity> &player) {
    sendMessageSync("LOGIN " + my_id_ + "\n");
    std::cout << "LOGIN " + my_id_ + "\n" << std::endl;
    recursRead(player);
}

void ClientOpenUDP::run(unsigned int my_id, std::shared_ptr<StateManager> state_manager) {
    // for (std::shared_ptr<Entity> entity: entities_->getEntities()) {
    //     if (entity->getType() != 4)
    //         continue;
    //     std::shared_ptr<Cooldown> cooldown = entity->getComponentByType<Cooldown>(CONFIG::CompType::TIMECOMP);
    //     if (cooldown == nullptr)
    //         continue;
    //     cooldown->create(1, "delete");
    //     if (cooldown->isFinish("delete")) {
    //         entities_->deleteEntity(entity->getUuid());
    //         break;
    //     }
    // }
    while (state_manager->isRunning()) {
        readMessageGlobal(my_id);
    }
    // std::cout << "size: " << entities_->getEntities().size() << std::endl;
    ioService.stop();
}
