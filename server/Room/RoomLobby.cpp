/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Room.cpp
*/

#include "RoomLobby.hpp"
#include <atomic>

std::atomic<bool> shouldStop(false);

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
        _thread = std::thread(&RoomLobby::gameEntryPoint, this);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

void RoomLobby::gameEntryPoint()
{
    std::cout << "Room " << _name << " started" << std::endl;
    EntityManager entityManager;
    int id = 0;
    int id_comp = 0;
    for (std::shared_ptr<PlayerLobby> &player : _players) {
        Entity player_entity(id);
        Position position(CONFIG::CompType::POSITION, id_comp, 0, 0);
        Health health(CONFIG::CompType::HEALTH, id_comp, 100);
        player_entity.addComponent(position);
        player_entity.addComponent(health);
        entityManager.addEntity(player_entity);
        id++, id_comp++;
    }

    Engine game(entityManager);
    // apl du serv-------------
    boost::asio::io_service io_service;
    std::thread t1([&io_service, &game](){ UDPServer server(io_service, 4242, std::make_shared<EntityManager>(game._manager)); });
    std::thread t([&io_service](){ io_service.run(); });
    // --------------------------
    game.run();

    while (!shouldStop.load(std::memory_order_relaxed)) {
        std::cout << "Room " << _name << " is running" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
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
        _isStarted = true;
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
