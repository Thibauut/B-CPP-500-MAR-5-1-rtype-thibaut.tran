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

    // if (my_id == "1") {
    //     std::shared_ptr<Entity> newP = std::make_shared<Entity>(stoi(my_id), 1);

    //     std::shared_ptr<Health> healthComponent = std::make_shared<Health>(CONFIG::CompType::HEALTH, stoi(my_id), 100);
    //     std::shared_ptr<Velocity> velocityComponent = std::make_shared<Velocity>(CONFIG::CompType::VELOCITY, stoi(my_id), 1);
    //     std::shared_ptr<Weapon> weaponComponent = std::make_shared<Weapon>(CONFIG::CompType::WEAPON, stoi(my_id), 1, 1, 1, 1, 1);
    //     std::shared_ptr<Position> positionComponent = std::make_shared<Position>(CONFIG::CompType::POSITION, stoi(my_id), 300, 300);

    //     std::shared_ptr<Sprite> spriteComponent = std::make_shared<Sprite>(CONFIG::CompType::SPRITE, stoi(my_id));
    //     sf::IntRect spriteRect(0, 0, std::round(33.2), std::round(17.2));
    //     // spriteComponent->setSprite(positionComponent->getPositionX(), positionComponent->getPositionY(), "assets/sprites/r-typesheet42.gif", spriteRect, sf::Vector2f(3, 3));

    //     newP->addComponent(healthComponent);
    //     newP->addComponent(velocityComponent);
    //     newP->addComponent(weaponComponent);
    //     newP->addComponent(positionComponent);
    //     newP->addComponent(spriteComponent);

    //     playersEntity_.push_back(newP);

    // } else if (my_id == "2") {
    //     std::shared_ptr<Entity> newP = std::make_shared<Entity>(stoi(my_id), 1);

    //     std::shared_ptr<Health> healthComponent = std::make_shared<Health>(CONFIG::CompType::HEALTH, stoi(my_id), 100);
    //     std::shared_ptr<Velocity> velocityComponent = std::make_shared<Velocity>(CONFIG::CompType::VELOCITY, stoi(my_id), 1);
    //     std::shared_ptr<Weapon> weaponComponent = std::make_shared<Weapon>(CONFIG::CompType::WEAPON, stoi(my_id), 1, 1, 1, 1, 1);
    //     std::shared_ptr<Position> positionComponent = std::make_shared<Position>(CONFIG::CompType::POSITION, stoi(my_id), 300, 400);

    //     sf::IntRect spriteRect(0, std::round(17.2), std::round(33.2), std::round(17.2));
    //     std::shared_ptr<Sprite> spriteComponent = std::make_shared<Sprite>(CONFIG::CompType::SPRITE, stoi(my_id));
    //     // spriteComponent->setSprite(positionComponent->getPositionX(), positionComponent->getPositionY(), "assets/sprites/r-typesheet42.gif", spriteRect, sf::Vector2f(3, 3));

    //     newP->addComponent(healthComponent);
    //     newP->addComponent(velocityComponent);
    //     newP->addComponent(weaponComponent);
    //     newP->addComponent(positionComponent);
    //     newP->addComponent(spriteComponent);

    //     playersEntity_.push_back(newP);
    // } else if (my_id == "3") {
    //    std::shared_ptr<Entity> newP = std::make_shared<Entity>(stoi(my_id), 1);

    //     std::shared_ptr<Health> healthComponent = std::make_shared<Health>(CONFIG::CompType::HEALTH, stoi(my_id), 100);
    //     std::shared_ptr<Velocity> velocityComponent = std::make_shared<Velocity>(CONFIG::CompType::VELOCITY, stoi(my_id), 1);
    //     std::shared_ptr<Weapon> weaponComponent = std::make_shared<Weapon>(CONFIG::CompType::WEAPON, stoi(my_id), 1, 1, 1, 1, 1);
    //     std::shared_ptr<Position> positionComponent = std::make_shared<Position>(CONFIG::CompType::POSITION, stoi(my_id), 300, 500);

    //     sf::IntRect spriteRect(0, std::round(34.4), std::round(33.2), std::round(17.2));
    //     std::shared_ptr<Sprite> spriteComponent = std::make_shared<Sprite>(CONFIG::CompType::SPRITE, stoi(my_id));
    //     // spriteComponent->setSprite(positionComponent->getPositionX(), positionComponent->getPositionY(), "assets/sprites/r-typesheet42.gif", spriteRect, sf::Vector2f(3, 3));

    //     newP->addComponent(healthComponent);
    //     newP->addComponent(velocityComponent);
    //     newP->addComponent(weaponComponent);
    //     newP->addComponent(positionComponent);
    //     newP->addComponent(spriteComponent);

    //     playersEntity_.push_back(newP);
    // } else if (my_id == "4") {
    //    std::shared_ptr<Entity> newP = std::make_shared<Entity>(stoi(my_id), 1);
    //     std::shared_ptr<Health> healthComponent = std::make_shared<Health>(CONFIG::CompTtypesheet42e::HEALTH, stoi(my_id), 100);
    //     std::shared_ptr<Velocity> velocityComponent = std::make_shared<Velocity>(CONFIG::CompType::VELOCITY, stoi(my_id), 1);
    //     std::shared_ptr<Weapon> weaponComponent = std::make_shared<Weapon>(CONFIG::CompType::WEAPON, stoi(my_id), 1, 1, 1, 1, 1);
    //     std::shared_ptr<Position> positionComponent = std::make_shared<Position>(CONFIG::CompType::POSITION, stoi(my_id), 300, 600);

    //     sf::IntRect spriteRect(0, std::round(51.6), std::round(33.2), std::round(17.2));
    //     std::shared_ptr<Sprite> spriteComponent = std::make_shared<Sprite>(CONFIG::CompType::SPRITE, stoi(my_id));
    //     // spriteComponent->setSprite(positionComponent->getPositionX(), positionComponent->getPositionY(), "assets/sprites/r-typesheet42.gif", spriteRect, sf::Vector2f(3, 3));

    //     newP->addComponent(healthComponent);
    //     newP->addComponent(velocityComponent);
    //     newP->addComponent(weaponComponent);
    //     newP->addComponent(positionComponent);
    //     newP->addComponent(spriteComponent);

    //     playersEntity_.push_back(newP);
    // }
}

bool ClientOpenUDP::sendMessageSync(const std::string& msg)
{
    socket_.send_to(boost::asio::buffer(msg), endpoint_);
    return true;
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
    // std::cout << "Entity type: " << received_obj.getType() << std::endl;
    // std::cout << "Entity id: " << received_obj.getId() << std::endl;
    // std::cout << "Pos: x: " << received_obj.getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPositionX() << " y: " << received_obj.getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPositionY() << std::endl;
    return received_obj;
}

bool ClientOpenUDP::readMessageGlobal()
{
    std::array<char, 1024> buffer;
    boost::asio::ip::udp::endpoint senderEndpoint;
    size_t size = socket_.receive_from(boost::asio::buffer(buffer), senderEndpoint);

    std::shared_ptr<Entity> ent = std::make_shared<Entity>(deserialize(std::string(buffer.data(), size)));
    if (ent == nullptr)
        return false;

    bool isExist = false;
    for (std::shared_ptr<Entity> &entity: entities_->getEntities()) {
        if (entity->getId() == ent->getId()) {
            isExist = true;
            entity->getComponentByType<Position>(CONFIG::CompType::POSITION)->setPositionX(ent->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionX());
            entity->getComponentByType<Position>(CONFIG::CompType::POSITION)->setPositionY(ent->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionY());
            entity->getComponentByType<Sprite>(CONFIG::CompType::SPRITE)->setPositionSprite(sf::Vector2f(ent->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionX(), ent->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionY()));
            break;
        }
    }
    if (!isExist && ent->getId() != std::stoi(my_id_)) {
        std::cout << "Create an entity" << std::endl;
        entities_->createEntity();
        std::shared_ptr<Sprite> spriteComp = ent->getComponentByType<Sprite>(CONFIG::CompType::SPRITE);
        if (spriteComp) {
            spriteComp->initSprite();
        }
        entities_->addEntity(*ent.get());
    }

    // for (std::shared_ptr<Entity> &pl: playersEntity_) {
    //     if (std::stoi(my_id_) == ent->getId()) {
    //         if (ent->getId() == 1)
    //             is1 = true;
    //         else if (ent->getId() == 2)
    //             is2 = true;
    //         else if (ent->getId() == 3)
    //             is3 = true;
    //         else if (ent->getId() == 4)
    //             is4 = true;
    //     }
    //     if (ent->getId() == 1 && !is1) {
    //         sf::IntRect spriteRect(0, 0, std::round(33.2), std::round(17.2));
    //         // ent->getComponentByType<Sprite>(CONFIG::CompType::SPRITE)->setSprite(ent->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionX(), ent->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionY(), "assets/sprites/r-typesheet42.gif", spriteRect, sf::Vector2f(3, 3));
    //         playersEntity_.push_back(ent);
    //         is1 = true;
    //     }
    //     else if (ent->getId() == 2 && !is2) {
    //         sf::IntRect spriteRect(0, std::round(17.2), std::round(33.2), std::round(17.2));
    //         // ent->getComponentByType<Sprite>(CONFIG::CompType::SPRITE)->setSprite(ent->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionX(), ent->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionY(), "assets/sprites/r-typesheet42.gif", spriteRect, sf::Vector2f(3, 3));
    //         playersEntity_.push_back(ent);
    //         is2 = true;
    //     }
    //     else if (ent->getId() == 3 && !is3) {
    //         sf::IntRect spriteRect(0, std::round(34.4), std::round(33.2), std::round(17.2));
    //         // ent->getComponentByType<Sprite>(CONFIG::CompType::SPRITE)->setSprite(ent->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionX(), ent->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionY(), "assets/sprites/r-typesheet42.gif", spriteRect, sf::Vector2f(3, 3));
    //         playersEntity_.push_back(ent);
    //         is3 = true;
    //     }
    //     else if (ent->getId() == 4 && !is4) {
    //         sf::IntRect spriteRect(0, std::round(51.6), std::round(33.2), std::round(17.2));
    //         // ent->getComponentByType<Sprite>(CONFIG::CompType::SPRITE)->setSprite(ent->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionX(), ent->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionY(), "assets/sprites/r-typesheet42.gif", spriteRect, sf::Vector2f(3, 3));
    //         playersEntity_.push_back(ent);
    //         is4 = true;
    //     }
    // }
    // for (std::shared_ptr<Entity> &pl: playersEntity_) {
    //     if (pl->getId() !=  std::stoi(my_id_) && pl->getId() == ent->getId()) {
    //         int posX = ent.get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPositionX();
    //         int posY = ent.get()->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPositionY();
    //         pl->getComponentByType<Position>(CONFIG::CompType::POSITION)->setPositionX(posX);
    //         pl->getComponentByType<Position>(CONFIG::CompType::POSITION)->setPositionY(posY);
    //         pl->getComponentByType<Sprite>(CONFIG::CompType::SPRITE)->setPositionSprite(sf::Vector2f(posX, posY));
    //     }
    // }

    //----------------------------------------------------------------
    //----------------------------------------------------------------

    // std::istringstream iss(buffer.data());
    // std::string line;

    // int id, posX, posY;
    // if (!iss) {
    //     std::cerr << "Erreur de parsing." << std::endl;
    //     return false;
    // }

    // while (iss >> id >> posX >> posY) {
    //     playerPositions[id] = {posX, posY};
    // }

    // for (const auto& entry : playerPositions) {
    //     if (entry.first == std::stoi(my_id_)) {
    //         if (entry.first == 1)
    //             is1 = true;
    //         else if (entry.first == 2)
    //             is2 = true;
    //         else if (entry.first == 3)
    //             is3 = true;
    //         else if (entry.first == 4)
    //             is4 = true;
    //     }

    //     if (entry.first != std::stoi(my_id_)) {
    //         if (entry.first == 1 && !is1) {
    //             std::shared_ptr<Entity> newP = std::make_shared<Entity>(entry.first);

    //             std::shared_ptr<Health> healthComponent = std::make_shared<Health>(CONFIG::CompType::HEALTH, entry.first, 100);
    //             std::shared_ptr<Velocity> velocityComponent = std::make_shared<Velocity>(CONFIG::CompType::VELOCITY, entry.first, 1);
    //             std::shared_ptr<Weapon> weaponComponent = std::make_shared<Weapon>(CONFIG::CompType::WEAPON, entry.first, 1, 1, 1, 1, 1);
    //             std::shared_ptr<Position> positionComponent = std::make_shared<Position>(CONFIG::CompType::POSITION, entry.first, entry.second.posX, entry.second.posY);

    //             std::shared_ptr<Sprite> spriteComponent = std::make_shared<Sprite>(CONFIG::CompType::SPRITE, entry.first);
    //             sf::IntRect spriteRect(0, 0, std::round(33.2), std::round(17.2));
    //             spriteComponent->setSprite(positionComponent->getPositionX(), positionComponent->getPositionY(), "assets/sprites/r-typesheet42.gif", spriteRect, sf::Vector2f(3, 3));

    //             newP->addComponent(healthComponent);
    //             newP->addComponent(velocityComponent);
    //             newP->addComponent(weaponComponent);
    //             newP->addComponent(positionComponent);
    //             newP->addComponent(spriteComponent);

    //             playersEntity_.push_back(newP);
    //             is1 = true;
    //         }
    //         else if (entry.first == 2 && !is2) {
    //             std::shared_ptr<Entity> newP = std::make_shared<Entity>(entry.first);

    //             std::shared_ptr<Health> healthComponent = std::make_shared<Health>(CONFIG::CompType::HEALTH, entry.first, 100);
    //             std::shared_ptr<Velocity> velocityComponent = std::make_shared<Velocity>(CONFIG::CompType::VELOCITY, entry.first, 1);
    //             std::shared_ptr<Weapon> weaponComponent = std::make_shared<Weapon>(CONFIG::CompType::WEAPON, entry.first, 1, 1, 1, 1, 1);
    //             std::shared_ptr<Position> positionComponent = std::make_shared<Position>(CONFIG::CompType::POSITION, entry.first, entry.second.posX, entry.second.posY);

    //             std::shared_ptr<Sprite> spriteComponent = std::make_shared<Sprite>(CONFIG::CompType::SPRITE, entry.first);
    //             sf::IntRect spriteRect(0, std::round(17.2), std::round(33.2), std::round(17.2));
    //             spriteComponent->setSprite(positionComponent->getPositionX(), positionComponent->getPositionY(), "assets/sprites/r-typesheet42.gif", spriteRect, sf::Vector2f(3, 3));

    //             newP->addComponent(healthComponent);
    //             newP->addComponent(velocityComponent);
    //             newP->addComponent(weaponComponent);
    //             newP->addComponent(positionComponent);
    //             newP->addComponent(spriteComponent);

    //             playersEntity_.push_back(newP);
    //             is2 = true;
    //         }
    //         else if (entry.first == 3 && !is3) {
    //             std::shared_ptr<Entity> newP = std::make_shared<Entity>(entry.first);

    //             std::shared_ptr<Health> healthComponent = std::make_shared<Health>(CONFIG::CompType::HEALTH, entry.first, 100);
    //             std::shared_ptr<Velocity> velocityComponent = std::make_shared<Velocity>(CONFIG::CompType::VELOCITY, entry.first, 1);
    //             std::shared_ptr<Weapon> weaponComponent = std::make_shared<Weapon>(CONFIG::CompType::WEAPON, entry.first, 1, 1, 1, 1, 1);
    //             std::shared_ptr<Position> positionComponent = std::make_shared<Position>(CONFIG::CompType::POSITION, entry.first, entry.second.posX, entry.second.posY);

    //             std::shared_ptr<Sprite> spriteComponent = std::make_shared<Sprite>(CONFIG::CompType::SPRITE, entry.first);
    //             sf::IntRect spriteRect(0, std::round(34.4), std::round(33.2), std::round(17.2));
    //             spriteComponent->setSprite(positionComponent->getPositionX(), positionComponent->getPositionY(), "assets/sprites/r-typesheet42.gif", spriteRect, sf::Vector2f(3, 3));

    //             newP->addComponent(healthComponent);
    //             newP->addComponent(velocityComponent);
    //             newP->addComponent(weaponComponent);
    //             newP->addComponent(positionComponent);
    //             newP->addComponent(spriteComponent);

    //             playersEntity_.push_back(newP);
    //             is3 = true;
    //         }
    //         else if (entry.first == 4 && !is4) {
    //             std::shared_ptr<Entity> newP = std::make_shared<Entity>(entry.first);

    //             std::shared_ptr<Health> healthComponent = std::make_shared<Health>(CONFIG::CompType::HEALTH, entry.first, 100);
    //             std::shared_ptr<Velocity> velocityComponent = std::make_shared<Velocity>(CONFIG::CompType::VELOCITY, entry.first, 1);
    //             std::shared_ptr<Weapon> weaponComponent = std::make_shared<Weapon>(CONFIG::CompType::WEAPON, entry.first, 1, 1, 1, 1, 1);
    //             std::shared_ptr<Position> positionComponent = std::make_shared<Position>(CONFIG::CompType::POSITION, entry.first, entry.second.posX, entry.second.posY);

    //             std::shared_ptr<Sprite> spriteComponent = std::make_shared<Sprite>(CONFIG::CompType::SPRITE, entry.first);
    //             sf::IntRect spriteRect(0, std::round(51.6), std::round(33.2), std::round(17.2));
    //             spriteComponent->setSprite(positionComponent->getPositionX(), positionComponent->getPositionY(), "assets/sprites/r-typesheet42.gif", spriteRect, sf::Vector2f(3, 3));

    //             newP->addComponent(healthComponent);
    //             newP->addComponent(velocityComponent);
    //             newP->addComponent(weaponComponent);
    //             newP->addComponent(positionComponent);
    //             newP->addComponent(spriteComponent);

    //             playersEntity_.push_back(newP);
    //             is4 = true;
    //         }
    //     }
    // }

    // for (std::shared_ptr<Entity> &pl: playersEntity_) {
    //     if (pl->getId() != std::stoi(my_id_)) {
    //         pl->getComponentByType<Position>(CONFIG::CompType::POSITION)->setPositionX(playerPositions[pl->getId()].posX);
    //         pl->getComponentByType<Position>(CONFIG::CompType::POSITION)->setPositionY(playerPositions[pl->getId()].posY);
    //         pl->getComponentByType<Sprite>(CONFIG::CompType::SPRITE)->setPositionSprite(sf::Vector2f(pl->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionX(), pl->getComponentByType<Position>(CONFIG::CompType::POSITION)->getPositionY()));
    //     }
    // }

    return false;
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
    std::cout << "UDP running" << std::endl;


    // if (!playersEntity_.empty()) {
    //     for (std::shared_ptr<Entity> &pl: playersEntity_) {
    //         if (pl->getId() == std::stoi(my_id_)) {
    //             sendMessageSync(serialize(pl));
    //         }
    //     }
    // }

    while (true) {
        readMessageGlobal();
    }

    ioService.stop();
}