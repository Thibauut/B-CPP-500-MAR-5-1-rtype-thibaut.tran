/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Room.cpp
*/

#include "RoomLobby.hpp"
#include <atomic>
#include <random>

std::atomic<bool> shouldStop(false);

unsigned short findOpenPort() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1024, 50000);
    unsigned short nombreAleatoire = dis(gen);
    return nombreAleatoire;
}

RoomLobby::RoomLobby(std::shared_ptr<PlayerLobby> owner, unsigned int nbSlots, std::string name, std::string uuid) : _owner(owner)
{
    _players.push_back(owner);
    _nbPlayers = 1;
    _nbSlots = nbSlots;
    _name = name;
    _uuid = uuid;
    _nbReadyPlayers = 0;
    _isStarted = false;
}

RoomLobby::~RoomLobby() {
    stopGame();
}

void RoomLobby::startGame()
{
    try {
        _isStarted = true;
        _port = findOpenPort();
        std::cout << "Le port "<< _port<< " est libre." << std::endl;
        _thread = std::thread(&RoomLobby::gameEntryPoint, this);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void RoomLobby::gameEntryPoint()
{
    std::cout << "Room " << _name << " started" << std::endl;
    EntityManager entityManager;
    int id = 1;
    int id_comp = 0;
    Position position = Position(CONFIG::CompType::POSITION, id_comp, 200, 300);
    Health health = Health(CONFIG::CompType::HEALTH, id_comp, 100);
    Sprite sprite = Sprite(CONFIG::CompType::SPRITE, id_comp);

    Weapon weapon = Weapon(
        CONFIG::CompType::WEAPON,
        id_comp,
        CONFIG::WeaponType::Weapon1
    );
    for (std::shared_ptr<PlayerLobby> player : _players) {
        entityManager.createEntity();
        Entity player_entity(id, 1);
        player_entity.setId(id);
        health.setId(id_comp);
        sf::IntRect spriteRect(0, 0, std::round(33.2), std::round(17.2));
        HitBoxSquare hitbox = HitBoxSquare(CONFIG::CompType::HITBOXSQUARE, id_comp, spriteRect);
        sprite.setSprite(position.getPositionX(), position.getPositionY(), "assets/sprites/r-typesheet42.gif", sf::Vector2f(3, 3), spriteRect);
        id_comp++;
        sprite.setId(id_comp);
        id_comp++;
        position.setId(id_comp);
        id_comp++;
        weapon.setId(id_comp);
        id_comp++;
        hitbox.setId(id_comp);
        std::shared_ptr<Position> positionShared = std::make_shared<Position>(position);
        std::shared_ptr<Health> healthShared = std::make_shared<Health>(health);
        std::shared_ptr<Sprite> spriteShared = std::make_shared<Sprite>(sprite);
        std::shared_ptr<Weapon> weaponShared = std::make_shared<Weapon>(weapon);
        std::shared_ptr<HitBoxSquare> hitboxShared = std::make_shared<HitBoxSquare>(hitbox);
        player_entity.addComponent(positionShared);
        player_entity.addComponent(healthShared);
        player_entity.addComponent(spriteShared);
        player_entity.addComponent(weaponShared);
        player_entity.addComponent(hitboxShared);
        entityManager.addEntity(player_entity);
        id++, id_comp++;
    }
    // Add mob entity
    id = 100;
    position = Position(CONFIG::CompType::POSITION, id_comp, 1600, 300);
    health = Health(CONFIG::CompType::HEALTH, id_comp, 100);
    sprite = Sprite(CONFIG::CompType::SPRITE, id_comp);
    AI ai = AI(CONFIG::CompType::AI, CONFIG::AiType::MOB1, id_comp, 0.005);
    Entity mob_entity(id, 2);
    mob_entity.setId(id);
    health.setId(id_comp);
    id_comp++;
    sprite.setId(id_comp);
    id_comp++;
    position.setId(id_comp);
    id_comp++;
    ai.setId(id_comp);
    sf::IntRect spriteRect(0, 0, std::round(33.3125), 36);
    HitBoxSquare hitbox = HitBoxSquare(CONFIG::CompType::HITBOXSQUARE, id_comp, spriteRect);
    sprite.setSprite(position.getPositionX(), position.getPositionY(), "assets/sprites/r-typesheet5.gif", sf::Vector2f(3, 3), spriteRect);
    std::shared_ptr<Position> positionShared = std::make_shared<Position>(position);
    std::shared_ptr<Health> healthShared = std::make_shared<Health>(health);
    std::shared_ptr<Sprite> spriteShared = std::make_shared<Sprite>(sprite);
    std::shared_ptr<HitBoxSquare> hitboxShared = std::make_shared<HitBoxSquare>(hitbox);
    std::shared_ptr<AI> aiShared = std::make_shared<AI>(ai);
    mob_entity.addComponent(positionShared);
    mob_entity.addComponent(healthShared);
    mob_entity.addComponent(spriteShared);
    mob_entity.addComponent(aiShared);
    mob_entity.addComponent(hitboxShared);
    entityManager.addEntity(mob_entity);

    // ---------------------------------
    Engine game(entityManager);
    game.addSystem(std::make_shared<SysAI>(game.getManager()));
    game.addSystem(std::make_shared<SysWeapon>(game.getManager()));
    game.addSystem(std::make_shared<SysShoot>(game.getManager()));
    game.addSystem(std::make_shared<SysCollision>(game.getManager()));
    // apl du serv---------------

    boost::asio::io_context io_context = boost::asio::io_context();
    std::thread t([&io_context](){ io_context.run(); });
    std::thread t1([&io_context, &gamee = game, my_port = _port](){ UDPServer server(io_context, my_port, gamee.getManager()); });
    // --------------------------
    game.run();
    t1.join();
    t.join();

    // while (!shouldStop.load(std::memory_order_relaxed)) {
    //     std::cout << "Room " << _name << " is running" << std::endl;
    //     std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    // }
    std::cout << "Room " << _name << " stopped" << std::endl;
}

void RoomLobby::stopGame()
{
    shouldStop.store(true, std::memory_order_relaxed);
    if (_thread.joinable())
        _thread.join();
}

bool RoomLobby::addReadyPlayer()
{
    _nbReadyPlayers++;
    if (_nbReadyPlayers == _nbSlots) {
        return (true);
    }
    return (false);
}

std::string RoomLobby::getInfo()
{
    std::string info = "\"" + _name + "\" \"" + std::to_string(_nbPlayers) + "/" + std::to_string(_nbSlots) + "\" \"" + _owner.get()->getUsername() + "\" \"" + std::to_string(_owner.get()->getLevel()) + "\"";
    for (std::shared_ptr<PlayerLobby> &player : _players) {
        if (player.get()->getUuid() != _owner.get()->getUuid()) {
            info += " \"" + player.get()->getUsername() + "\" \"" + std::to_string(player.get()->getLevel()) + "\"";
        }
    }
    info += "\n";
    return info;
}

bool RoomLobby::addPlayer(std::shared_ptr<PlayerLobby> player)
{
    if (_nbPlayers == _nbSlots)
        return (false);
    _players.push_back(player);
    _nbPlayers++;
    return (true);
}

void RoomLobby::removePlayer(std::string uid)
{
    for (int i = 0; i < _players.size(); i++) {
        if (_players[i].get()->getUuid() == uid) {
            _players.erase(_players.begin() + i);
            _nbPlayers--;
            break;
        }
    }
}
