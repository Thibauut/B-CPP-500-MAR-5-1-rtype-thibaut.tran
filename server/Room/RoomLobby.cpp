/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Room.cpp
*/

#include "RoomLobby.hpp"
#include <atomic>
#include <random>

unsigned short findOpenPort() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1024, 50000);
    unsigned short nombreAleatoire = dis(gen);
    return nombreAleatoire;
}

RoomLobby::RoomLobby(std::shared_ptr<PlayerLobby> owner, unsigned int nbSlots, std::string name, std::string uuid, std::string pathMap, int gametype, std::string titleGame) : _owner(owner)
{
    _players.push_back(owner);
    _nbPlayers = 1;
    _nbSlots = nbSlots;
    _name = name;
    _uuid = uuid;
    _nbReadyPlayers = 0;
    _isStarted = false;
    _pathMap = pathMap;
    _gameType = gametype;
    _titleGame = titleGame;
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
        if (_gameType == 0)
            _thread = std::thread(&RoomLobby::gameEntryPoint, this);
        if (_gameType == 1)
            _thread = std::thread(&RoomLobby::PvpEntryPoint, this);
        if (_gameType == 2)
            _thread = std::thread(&RoomLobby::DuoPvpEntryPoint, this);
        if (_gameType == 3)
            _thread = std::thread(&RoomLobby::SurvivalEntryPoint, this);
        if (_gameType == 4)
        _thread = std::thread(&RoomLobby::BattleRoyalEntryPoint, this);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void RoomLobby::gameEntryPoint()
{
    std::cout << "Room " << _name << " started" << std::endl;
    std::cout << "GAME: " +  _titleGame << std::endl;
    if (_titleGame == "R-TYPE") {
       std::shared_ptr<EntityManager> entityManager = std::shared_ptr<EntityManager>(new EntityManager());
        int id = 1;
        int id_comp = 0;
        Position position = Position(CONFIG::CompType::POSITION, id_comp, 200, 300);
        Health health = Health(CONFIG::CompType::HEALTH, id_comp, 100);
        Sprite sprite = Sprite(CONFIG::CompType::SPRITE, id_comp);
        Direction direction = Direction (CONFIG::CompType::DIRECTION, id_comp, 1, 1, 0);
        Team team = Team(CONFIG::CompType::TEAM, id_comp+=1, 1);
        Sound soundBullet = Sound(CONFIG::CompType::SOUND, id_comp+=1, "assets/audio/gun.ogg");
        for (std::shared_ptr<PlayerLobby> player : _players) {
            std::cout << player->GetPlayerWeapons().size() << std::endl;
            player->setPlayerEquipedWeapon(player->GetPlayerWeapons()[0]);
            Weapon weapon = Weapon(CONFIG::CompType::WEAPON,id_comp, player->getEquipedWeapon()->type);
            weapon.setDegat(player->getEquipedWeapon()->degat);
            weapon.setCadence(player->getEquipedWeapon()->cadence);
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
        game.addSystem(std::make_shared<SysCamera>(game.getManager()));
        // apl du serv---------------
        boost::asio::io_context io_context = boost::asio::io_context();
        std::thread t([&io_context](){ io_context.run(); });
        std::thread t1([&io_context, &gamee = game, my_port = _port](){ UDPServer server(io_context, my_port, gamee.getManager()); });
        // --------------------------
        game.run();
        t1.join();
        t.join();


    }

    if (_titleGame == "PONG") {
        std::shared_ptr<EntityManager> entityManager = std::shared_ptr<EntityManager>(new EntityManager());
        int id = 1;
        int id_comp = 0;
        Sprite sprite = Sprite(CONFIG::CompType::SPRITE, id_comp);

        for (std::shared_ptr<PlayerLobby> player : _players) {
            entityManager->createEntity();
            Entity player_entity(id, id);
            player_entity.init();
            player_entity.setId(id);
            sf::IntRect spriteRect(0, 0, 70, 240);
            Position position;
            if (id == 1)
                position = Position(CONFIG::CompType::POSITION, id_comp, 0, 300);
            if (id == 2)
                position = Position(CONFIG::CompType::POSITION, id_comp, (1920 - 70), 400);
            HitBoxSquare hitbox = HitBoxSquare(CONFIG::CompType::HITBOXSQUARE, id_comp, spriteRect);
            sprite.setSprite(position.getPositionX(), position.getPositionY(), "assets/images/pongPlayer.png", sf::Vector2f(1, 1), spriteRect, CONFIG::SpriteType::PLAYERSPRITE);
            sprite.setMaxDimensions(70, 250);
            sprite.setId(id_comp+=1);
            position.setId(id_comp+=1);
            hitbox.setId(id_comp += 1);
            std::shared_ptr<Position> positionShared = std::make_shared<Position>(position);
            std::shared_ptr<Sprite> spriteShared = std::make_shared<Sprite>(sprite);
            std::shared_ptr<HitBoxSquare> hitboxShared = std::make_shared<HitBoxSquare>(hitbox);
            player_entity.addComponent(positionShared);
            player_entity.addComponent(spriteShared);
            player_entity.addComponent(hitboxShared);
            entityManager->addEntity(player_entity);
            id++, id_comp++;
        }
        // ---------------------------------
        if (_players.size() == 1) {
            Entity pongAi_entity = Entity(2);
            pongAi_entity.init();
            Position position = Position(CONFIG::CompType::POSITION, id_comp+=1, (1920 - 70), 400);
            HitBoxSquare hitbox = HitBoxSquare(CONFIG::CompType::HITBOXSQUARE, id_comp+=1);
            Cooldown coolDown = Cooldown(CONFIG::CompType::TIMECOMP, id_comp+=1);

            sf::IntRect spriteRect(0, 0, 70, 240);
            sprite.setSprite(position.getPositionX(), position.getPositionY(), "assets/images/pongPlayer.png", sf::Vector2f(1, 1), spriteRect, CONFIG::SpriteType::PLAYERSPRITEAI);
            sprite.setMaxDimensions(70, 250);
            hitbox.setHitboxSize(70, 250);
            AI ai = AI(CONFIG::CompType::AI, CONFIG::AiType::PLAYER, id_comp+=1, 1.0);

            std::shared_ptr<AI> aiShared = std::make_shared<AI>(ai);
            std::shared_ptr<Position> positionShared = std::make_shared<Position>(position);
            std::shared_ptr<Sprite> spriteShared = std::make_shared<Sprite>(sprite);
            std::shared_ptr<HitBoxSquare> hitboxShared = std::make_shared<HitBoxSquare>(hitbox);
            std::shared_ptr<Cooldown> coolDownShared = std::make_shared<Cooldown>(coolDown);

            pongAi_entity.addComponent(aiShared);
            pongAi_entity.addComponent(positionShared);
            pongAi_entity.addComponent(spriteShared);
            pongAi_entity.addComponent(hitboxShared);
            pongAi_entity.addComponent(coolDownShared);
            entityManager->addEntity(pongAi_entity);
        }

        Entity ballEntity = Entity(3);
        ballEntity.init();
        Position position = Position(CONFIG::CompType::POSITION, id_comp+=1, 1920/2 - 60/2, 1080/2 - 60/2);
        HitBoxSquare hitbox = HitBoxSquare(CONFIG::CompType::HITBOXSQUARE, id_comp+=1);
        Direction direction = Direction(CONFIG::CompType::DIRECTION, id_comp, 1, 1, 0);

        sf::IntRect spriteRect(0, 0, 60, 60);
        sprite.setSprite(position.getPositionX(), position.getPositionY(), "assets/images/ball.png", sf::Vector2f(1, 1), spriteRect, CONFIG::SpriteType::BALLSPRITE);
        sprite.setMaxDimensions(60, 60);
        sprite.initRect();
        hitbox.setHitboxSize(60, 60);


        std::shared_ptr<Position> positionShared = std::make_shared<Position>(position);
        std::shared_ptr<Sprite> spriteShared = std::make_shared<Sprite>(sprite);
        std::shared_ptr<HitBoxSquare> hitboxShared = std::make_shared<HitBoxSquare>(hitbox);
        std::shared_ptr<Direction> directionShared = std::make_shared<Direction>(direction);

        ballEntity.addComponent(directionShared);
        ballEntity.addComponent(positionShared);
        ballEntity.addComponent(spriteShared);
        ballEntity.addComponent(hitboxShared);
        entityManager->addEntity(ballEntity);

        Engine game(*entityManager.get());
        // ---------------------------------
        if (_players.size() == 1) {
            game.addSystem(std::make_shared<SysAIPong>(game.getManager()));
        }
        game.addSystem(std::make_shared<SysCollisionPong>(game.getManager()));
        game.addSystem(std::make_shared<SysMoveBallPong>(game.getManager()));
        // ---------------------------------
        boost::asio::io_context io_context = boost::asio::io_context();
        std::thread t([&io_context](){ io_context.run(); });
        std::thread t1([&io_context, &gamee = game, my_port = _port](){ UDPServer server(io_context, my_port, gamee.getManager()); });
        // --------------------------
        game.run();
        t1.join();
        t.join();
    }
    std::cout << "Room " << _name << " stopped" << std::endl;
}

void RoomLobby::PvpEntryPoint()
{
    std::cout << "Room PVP " << _name << " started" << std::endl;
        std::shared_ptr<EntityManager> entityManager = std::shared_ptr<EntityManager>(new EntityManager());
    int id = 1;
    int id_comp = 0;
    Health health = Health(CONFIG::CompType::HEALTH, id_comp, 100);
    Sprite sprite = Sprite(CONFIG::CompType::SPRITE, id_comp);

    Sound soundBullet = Sound(CONFIG::CompType::SOUND, id_comp+=1, "assets/audio/gun.ogg");
    int equipe = 1;
    int x = 200;
    int y = 300;
    for (std::shared_ptr<PlayerLobby> player : _players) {
         player->setPlayerEquipedWeapon(player->GetPlayerWeapons()[0]);
        Weapon weapon = Weapon(CONFIG::CompType::WEAPON,id_comp, player->getEquipedWeapon()->type);
        weapon.setDegat(player->getEquipedWeapon()->degat);
        weapon.setCadence(player->getEquipedWeapon()->cadence);
        Position position = Position(CONFIG::CompType::POSITION, id_comp, x, y);
        Direction direction = Direction (CONFIG::CompType::DIRECTION, id_comp, 1, 1, 0);
        Team team = Team(CONFIG::CompType::TEAM, id_comp+=1, equipe);
        equipe += 1;
        x += 200;
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
    // ---------------------------------
    Engine game(*entityManager.get());
    game.addSystem(std::make_shared<SysAI>(game.getManager()));
    game.addSystem(std::make_shared<SysWeapon>(game.getManager()));
    game.addSystem(std::make_shared<SysShoot>(game.getManager()));
    game.addSystem(std::make_shared<SysCollision>(game.getManager()));
    game.addSystem(std::make_shared<SysClear>(game.getManager()));
    game.addSystem(std::make_shared<SysCamera>(game.getManager()));
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

void RoomLobby::BattleRoyalEntryPoint()
{
    std::cout << "BR Started" << std::endl;
    std::shared_ptr<EntityManager> entityManager = std::shared_ptr<EntityManager>(new EntityManager());
    int id = 1;
    int id_comp = 0;
    Health health = Health(CONFIG::CompType::HEALTH, id_comp, 100);
    Sprite sprite = Sprite(CONFIG::CompType::SPRITE, id_comp);
    Sound soundBullet = Sound(CONFIG::CompType::SOUND, id_comp+=1, "assets/audio/gun.ogg");
    int equipe = 1;
    int x = 200;
    int y = 300;
    for (std::shared_ptr<PlayerLobby> player : _players) {
        player->setPlayerEquipedWeapon(player->GetPlayerWeapons()[0]);
        Weapon weapon = Weapon(CONFIG::CompType::WEAPON,id_comp, player->getEquipedWeapon()->type);
        weapon.setDegat(player->getEquipedWeapon()->degat);
        weapon.setCadence(player->getEquipedWeapon()->cadence);
        Position position = Position(CONFIG::CompType::POSITION, id_comp, x, y);
        Direction direction = Direction (CONFIG::CompType::DIRECTION, id_comp, 1, 1, 0);
        Team team = Team(CONFIG::CompType::TEAM, id_comp+=1, equipe);
        equipe += 1;
        x += 200;
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
    // ---------------------------------
    Engine game(*entityManager.get());
    game.addSystem(std::make_shared<SysAI>(game.getManager()));
    game.addSystem(std::make_shared<SysWeapon>(game.getManager()));
    game.addSystem(std::make_shared<SysShoot>(game.getManager()));
    game.addSystem(std::make_shared<SysCollision>(game.getManager()));
    game.addSystem(std::make_shared<SysClear>(game.getManager()));
    game.addSystem(std::make_shared<SysCamera>(game.getManager()));
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
void RoomLobby::DuoPvpEntryPoint()
{
    std::cout << "DUO PVP STARTED" << std::endl;
    std::shared_ptr<EntityManager> entityManager = std::shared_ptr<EntityManager>(new EntityManager());
    int id = 1;
    int id_comp = 0;
    Health health = Health(CONFIG::CompType::HEALTH, id_comp, 100);
    Sprite sprite = Sprite(CONFIG::CompType::SPRITE, id_comp);

    Sound soundBullet = Sound(CONFIG::CompType::SOUND, id_comp+=1, "assets/audio/gun.ogg");
    int equipe = 1;
    int team_count = 0;
    int x = 200;
    int y = 300;
    for (std::shared_ptr<PlayerLobby> player : _players) {
        if (team_count == 2) {
            equipe += 1;
            team_count = 0;
        }
         player->setPlayerEquipedWeapon(player->GetPlayerWeapons()[0]);
        Weapon weapon = Weapon(CONFIG::CompType::WEAPON,id_comp, player->getEquipedWeapon()->type);
        weapon.setDegat(player->getEquipedWeapon()->degat);
        weapon.setCadence(player->getEquipedWeapon()->cadence);
        team_count++;
        Position position = Position(CONFIG::CompType::POSITION, id_comp, x, y);
        Direction direction = Direction (CONFIG::CompType::DIRECTION, id_comp, 1, 1, 0);
        Team team = Team(CONFIG::CompType::TEAM, id_comp+=1, equipe);
        x += 200;
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
    // ---------------------------------
    Engine game(*entityManager.get());
    game.addSystem(std::make_shared<SysAI>(game.getManager()));
    game.addSystem(std::make_shared<SysWeapon>(game.getManager()));
    game.addSystem(std::make_shared<SysShoot>(game.getManager()));
    game.addSystem(std::make_shared<SysCollision>(game.getManager()));
    game.addSystem(std::make_shared<SysClear>(game.getManager()));
    game.addSystem(std::make_shared<SysCamera>(game.getManager()));
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
void RoomLobby::SurvivalEntryPoint()
{
    std::cout << "SURVIVAL STARTED quand mao aura décidé de le faire ce gros tchoupeur" << std::endl;
}
void RoomLobby::stopGame()
{
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
