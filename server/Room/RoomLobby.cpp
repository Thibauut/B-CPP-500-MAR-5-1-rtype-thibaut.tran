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

RoomLobby::RoomLobby(std::shared_ptr<PlayerLobby> owner, unsigned int nbSlots, std::string name, std::string uuid, std::string pathMap) : _owner(owner)
{
    _players.push_back(owner);
    _nbPlayers = 1;
    _nbSlots = nbSlots;
    _name = name;
    _uuid = uuid;
    _nbReadyPlayers = 0;
    _isStarted = false;
    _pathMap = pathMap;
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
    std::shared_ptr<EntityManager> entityManager = std::shared_ptr<EntityManager>(new EntityManager());
    int id = 1;
    int id_comp = 0;
    Position position = Position(CONFIG::CompType::POSITION, id_comp, 200, 300);
    Health health = Health(CONFIG::CompType::HEALTH, id_comp, 100);
    Sprite sprite = Sprite(CONFIG::CompType::SPRITE, id_comp);
    Direction direction = Direction (CONFIG::CompType::DIRECTION, id_comp, 1, 0);
    Team team = Team(CONFIG::CompType::TEAM, id_comp+=1, 1);

    Sound soundBullet = Sound(CONFIG::CompType::SOUND, id_comp+=1, "assets/audio/gun.ogg");

    Weapon weapon = Weapon(
        CONFIG::CompType::WEAPON,
        id_comp,
        CONFIG::WeaponType::Weapon3
    );
    for (std::shared_ptr<PlayerLobby> player : _players) {
        entityManager->createEntity();
        Entity player_entity(id, 1);
        player_entity.init();
        player_entity.setId(id);
        health.setId(id_comp);
        sf::IntRect spriteRect(100, id * 17, std::round(33.2), std::round(17.2));
        HitBoxSquare hitbox = HitBoxSquare(CONFIG::CompType::HITBOXSQUARE, id_comp, spriteRect);
        sprite.setSprite(position.getPositionX(), position.getPositionY(), "assets/sprites/r-typesheet42.gif", sf::Vector2f(3, 3), spriteRect, CONFIG::SpriteType::PLAYERSPRITE);
        sprite.setMaxDimensions(166, 86);
        sprite.setId(id_comp+=1);
        position.setId(id_comp+=1);
        weapon.setId(id_comp+=1);
        hitbox.setId(id_comp += 1);
        std::shared_ptr<Position> positionShared = std::make_shared<Position>(position);
        std::shared_ptr<Health> healthShared = std::make_shared<Health>(health);
        std::shared_ptr<Sprite> spriteShared = std::make_shared<Sprite>(sprite);
        std::shared_ptr<Weapon> weaponShared = std::make_shared<Weapon>(weapon);
        std::shared_ptr<HitBoxSquare> hitboxShared = std::make_shared<HitBoxSquare>(hitbox);
        std::shared_ptr<Direction> directionShared = std::make_shared<Direction>(direction);
        std::shared_ptr<Team>teamShared = std::make_shared<Team>(team);
        std::shared_ptr<Sound>soundBulletShared = std::make_shared<Sound>(soundBullet);
        player_entity.addComponent(positionShared);
        player_entity.addComponent(healthShared);
        player_entity.addComponent(spriteShared);
        player_entity.addComponent(weaponShared);
        player_entity.addComponent(hitboxShared);
        player_entity.addComponent(directionShared);
        player_entity.addComponent(teamShared);
        player_entity.addComponent(soundBulletShared);
        entityManager->addEntity(player_entity);
        id++, id_comp++;
    }
    RType::Map map(_pathMap);
    map.loadMap(entityManager);
    // ---------------------------------
    Engine game(*entityManager.get());
    game.addSystem(std::make_shared<SysAI>(game.getManager()));
    game.addSystem(std::make_shared<SysWeapon>(game.getManager()));
    game.addSystem(std::make_shared<SysShoot>(game.getManager()));
    game.addSystem(std::make_shared<SysCollision>(game.getManager()));
    game.addSystem(std::make_shared<SysClear>(game.getManager()));
    // apl du serv---------------
    boost::asio::io_context io_context = boost::asio::io_context();
    std::thread t([&io_context](){ io_context.run(); });
    std::thread t1([&io_context, &gamee = game, my_port = _port](){ UDPServer server(io_context, my_port, gamee.getManager()); });
    // --------------------------
    game.run();
    t1.join();
    t.join();

    std::cout << "Room " << _name << " stopped" << std::endl;
}

void RoomLobby::PvpEntryPoint()
{
    std::cout << "Room PVP " << _name << " started" << std::endl;
    std::shared_ptr<EntityManager> entityManager = std::shared_ptr<EntityManager>(new EntityManager());
    int id = 1;
    int id_comp = 0;
    // ----------------------------------PLAYER 1---------------------------------
    Position position = Position(CONFIG::CompType::POSITION, id_comp, 200, 300);
    Health health = Health(CONFIG::CompType::HEALTH, id_comp, 100);
    Sprite sprite = Sprite(CONFIG::CompType::SPRITE, id_comp);
    Direction direction = Direction (CONFIG::CompType::DIRECTION, id_comp, 1, 0);
    Weapon weapon = Weapon(
        CONFIG::CompType::WEAPON,
        id_comp,
        CONFIG::WeaponType::Weapon3
    );
    Team team = Team(CONFIG::CompType::TEAM, id_comp+=1, 1);
    entityManager->createEntity();
    Entity player_entity(id, 1);
    player_entity.init();
    player_entity.setId(id);
    health.setId(id_comp);
    sf::IntRect spriteRect(0, id * 17, std::round(33.2), std::round(17.2));
    HitBoxSquare hitbox = HitBoxSquare(CONFIG::CompType::HITBOXSQUARE, id_comp, spriteRect);
    sprite.setSprite(position.getPositionX(), position.getPositionY(), "assets/sprites/r-typesheet42.gif", sf::Vector2f(3, 3), spriteRect, CONFIG::SpriteType::PLAYERSPRITE);
    sprite.setId(id_comp+=1);
    position.setId(id_comp+=1);
    weapon.setId(id_comp+=1);
    hitbox.setId(id_comp += 1);
    direction.setOrientation(0);
    std::shared_ptr<Position> positionShared = std::make_shared<Position>(position);
    std::shared_ptr<Health> healthShared = std::make_shared<Health>(health);
    std::shared_ptr<Sprite> spriteShared = std::make_shared<Sprite>(sprite);
    std::shared_ptr<Weapon> weaponShared = std::make_shared<Weapon>(weapon);
    std::shared_ptr<HitBoxSquare> hitboxShared = std::make_shared<HitBoxSquare>(hitbox);
    std::shared_ptr<Direction> directionShared = std::make_shared<Direction>(direction);
    std::shared_ptr<Team>teamShared = std::make_shared<Team>(team);
    player_entity.addComponent(positionShared);
    player_entity.addComponent(healthShared);
    player_entity.addComponent(spriteShared);
    player_entity.addComponent(weaponShared);
    player_entity.addComponent(hitboxShared);
    player_entity.addComponent(directionShared);
    player_entity.addComponent(teamShared);
    entityManager->addEntity(player_entity);
    id++, id_comp++;
    // ----------------------------------PLAYER 2---------------------------------

    Position position2 = Position(CONFIG::CompType::POSITION, id_comp, 1720, 300);
    Health health2 = Health(CONFIG::CompType::HEALTH, id_comp, 100);
    Sprite sprite2 = Sprite(CONFIG::CompType::SPRITE, id_comp);
    Direction direction2 = Direction (CONFIG::CompType::DIRECTION, id_comp, -1, 0);
    Weapon weapon2 = Weapon(
        CONFIG::CompType::WEAPON,
        id_comp,
        CONFIG::WeaponType::Weapon1
    );
    Team team2 = Team(CONFIG::CompType::TEAM, id_comp+=1, 2);
    entityManager->createEntity();
    Entity player_entity2(id, 1);
    player_entity2.init();
    player_entity2.setId(id);
    health2.setId(id_comp);
    sf::IntRect spriteRect2(0, id * 17, std::round(33.2), std::round(17.2));
    HitBoxSquare hitbox2 = HitBoxSquare(CONFIG::CompType::HITBOXSQUARE, id_comp, spriteRect2);
    sprite2.setSprite(position.getPositionX(), position.getPositionY(), "assets/sprites/r-typesheet42.gif", sf::Vector2f(3, 3), spriteRect2, CONFIG::SpriteType::PLAYERSPRITE);
    sprite2.setId(id_comp+=1);
    position2.setId(id_comp+=1);
    weapon2.setId(id_comp+=1);
    hitbox2.setId(id_comp += 1);
    direction2.setOrientation(180);
    std::shared_ptr<Position> positionShared2 = std::make_shared<Position>(position2);
    std::shared_ptr<Health> healthShared2 = std::make_shared<Health>(health2);
    std::shared_ptr<Sprite> spriteShared2 = std::make_shared<Sprite>(sprite2);
    std::shared_ptr<Weapon> weaponShared2 = std::make_shared<Weapon>(weapon2);
    std::shared_ptr<HitBoxSquare> hitboxShared2 = std::make_shared<HitBoxSquare>(hitbox2);
    std::shared_ptr<Direction> directionShared2 = std::make_shared<Direction>(direction2);
    std::shared_ptr<Team>teamShared2 = std::make_shared<Team>(team2);
    player_entity2.addComponent(positionShared2);
    player_entity2.addComponent(healthShared2);
    player_entity2.addComponent(spriteShared2);
    player_entity2.addComponent(weaponShared2);
    player_entity2.addComponent(hitboxShared2);
    player_entity2.addComponent(directionShared2);
    player_entity2.addComponent(teamShared2);
    entityManager->addEntity(player_entity2);
    // ---------------------------------
    Engine game(*entityManager.get());
    game.addSystem(std::make_shared<SysWeapon>(game.getManager()));
    game.addSystem(std::make_shared<SysShoot>(game.getManager()));
    game.addSystem(std::make_shared<SysCollision>(game.getManager()));
    game.addSystem(std::make_shared<SysClear>(game.getManager()));
    // apl du serv---------------
    boost::asio::io_context io_context = boost::asio::io_context();
    std::thread t([&io_context](){ io_context.run(); });
    std::thread t1([&io_context, &gamee = game, my_port = _port](){ UDPServer server(io_context, my_port, gamee.getManager()); });
    // --------------------------
    game.run();
    t1.join();
    t.join();
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
