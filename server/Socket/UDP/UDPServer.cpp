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
#define mob_type 2
#define bullet_type 3

UDPServer::UDPServer(boost::asio::io_context &io_context, unsigned short port, std::shared_ptr<EntityManager> entity_manager, std::shared_ptr<StateManager> state_manager)
    : socket_(io_context, udp::endpoint(udp::v4(), port)), entityManagerPtr_(entity_manager), stateManagerPtr_(state_manager) {
        port_ = port;
        remote_endpoints_.clear();
        // init();
        send_thread_ = std::thread(&UDPServer::sendThread, this);
        StartReceive();
        send_thread_.join();
}

void UDPServer::init() {
    bool isRunning = true;
    while (isRunning) {
        recv_buf_ = {0};
        size_t size = socket_.receive_from(boost::asio::buffer(recv_buf_), client);
        std::string message(recv_buf_.begin(), recv_buf_.end());
        handleReceive(message);
    }
}

void UDPServer::StartReceive() {
    while (stateManagerPtr_->isRunning()) {
        recv_buf_ = {0};
        size_t size = socket_.receive_from(boost::asio::buffer(recv_buf_), client);
        std::string message(recv_buf_.begin(), recv_buf_.end());
        if (message.find("STOP") != std::string::npos)
            break;
        handleReceive(message);
    }
    std::cout << "END" << std::endl;
}

void UDPServer::handleReceive(std::string &data) {
    if (EndpointExist(client) == false) {
        remote_endpoints_.push_back(std::make_shared<udp::endpoint>(client));
    }
    if (PlayerLogin(data, client) == false)
        StartExec(deserialize(data), client);
}

bool UDPServer::PlayerLogin(std::string data, udp::endpoint &client)
{
    std::istringstream splitedData(data);
    std::string word;
    std::vector <std::string> cmd;
    while (splitedData >> word)
        cmd.push_back(word);
    if (cmd[0] == "LOGIN") {
            int player_id = std::atoi(cmd[1].c_str());
            std::string serializedEntity = serialize(entityManagerPtr_->getEntityById(player_id));
            // compress
            Compressor compressor;
            std::string compressesEntity = compressor.compress(serializedEntity);
            // deserialize
            Entity entity = deserialize(serializedEntity);
            std::cout << "Player " << player_id << " connected" << std::endl;

            socket_.send_to(boost::asio::buffer(compressesEntity), client);

        return true;
    }
    return false;
}

void UDPServer::sendToClient(const std::string& message, udp::endpoint &client_t)
{
    std::string new_message = message + "\n";
    socket_.send_to(boost::asio::buffer(new_message), client_t);

}

void UDPServer::sendAll(const std::string& message, std::vector<std::shared_ptr<udp::endpoint>> &endpoints)
{
    for (std::shared_ptr<udp::endpoint> remote_client : endpoints) {
        try {
            Compressor compressor;
            std::string compressesEntity = compressor.compress(message);
            socket_.send_to(boost::asio::buffer(compressesEntity), *remote_client.get());
        } catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }
}


void  UDPServer::sendAllEntitys()
{
    std::lock_guard<std::mutex> lock(entityManagerPtr_->getMutex());
        for (std::shared_ptr<GameEngine::Entity> &Entity : entityManagerPtr_.get()->getEntities()) {
            if (Entity->getType() != 1 && Entity->getType() != 5)
                sendAll(serialize(Entity), remote_endpoints_);
        }
}

void UDPServer::sendThread() {
    std::this_thread::sleep_for(std::chrono::seconds(5));
    while (stateManagerPtr_->isRunning()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        sendAllEntitys();
    }
    boost::asio::ip::udp::endpoint localEndpoint(boost::asio::ip::address::from_string("127.0.0.1"), port_);
    sendToClient("STOP", localEndpoint);
    std::cout << "SEND THREAD STOPPED" << std::endl;
}

void UDPServer::setPlayerPosition(Entity &player)
{
    entityManagerPtr_->getEntity(player.getUuid())->getComponentByType<Position>(CONFIG::CompType::POSITION).get()->setPosition(
        player.getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPositionX(),
        player.getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPositionY()
    );
    std::shared_ptr<Score> entityScore = entityManagerPtr_->getEntity(player.getUuid())->getComponentByType<Score>(CONFIG::CompType::SCORE);
    if (entityScore) {
        player.getComponentByType<Score>(CONFIG::CompType::SCORE)->setScore(entityScore->getScore());
    }
    if (entityManagerPtr_->getEntity(player.getUuid())->getComponentByType<Weapon>(CONFIG::CompType::WEAPON).get()) {
        entityManagerPtr_->getEntity(player.getUuid())->getComponentByType<Weapon>(CONFIG::CompType::WEAPON).get()->setShooting(
            player.getComponentByType<Weapon>(CONFIG::CompType::WEAPON)->getIsShooting(),
            player.getComponentByType<Weapon>(CONFIG::CompType::WEAPON)->getTimePressed()
        );
    }
}

void UDPServer::StartExec(Entity entity, udp::endpoint &client) {
        if (entity.getType() == 1) {
            setPlayerPosition(entity);
            std::shared_ptr Entity_ptr = std::make_shared<Entity>(entity);
            sendAll(serialize(Entity_ptr), remote_endpoints_);
        }
        // if (entity.getType() == 2)
        //     setEntityPosition(entity, 2);
}