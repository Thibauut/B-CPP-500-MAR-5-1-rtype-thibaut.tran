#pragma once

#include <array>
#include <boost/asio.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/list.hpp>
#include <thread>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>
#include "../../../GameEngine/Entity/EntityManager/EntityManager.hpp"
#include "../../../GameEngine/Utils/Utils.hpp"
#include "../../../GameEngine/Components/Position/Position.hpp"

using boost::asio::ip::udp;

class UDPRequest {
    public:
        UDPRequest(std::string data, udp::endpoint &client): data_(data), client_(client) {}
        ~UDPRequest() {}
        std::string data_;
        udp::endpoint &client_;
};

class UDPServer {
public:
    UDPServer(boost::asio::io_context& io_context, unsigned short port, std::shared_ptr<EntityManager> entity_manager);
    bool EndpointExist(udp::endpoint client) {
        if (remote_endpoints_.empty()) {
            return false;
        }
        for (std::shared_ptr<udp::endpoint> tmp : remote_endpoints_) {
            if (tmp->address() == client.address()) {
                return true;
            }
        }
        return false;
    }

    std::string serialize(std::shared_ptr<Entity> entity) {
        std::ostringstream oss;
        boost::archive::binary_oarchive archive(oss);
        archive << *entity.get();
        return oss.str();
    }

    Entity deserialize(std::string serializedData) {
        std::istringstream received_data(serializedData);
        boost::archive::binary_iarchive ia(received_data);
        Entity received_obj(971);
        ia >> received_obj;
        std::cout << "Entity type: " << received_obj.getType() << std::endl;
        std::cout << "Entity id: " << received_obj.getId() << std::endl;
        std::cout << "Pos: x: " << received_obj.getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPositionX() << " y: " << received_obj.getComponentByType<Position>(CONFIG::CompType::POSITION).get()->getPositionY() << std::endl;
        return received_obj;
    }

    void StartReceive();
    void handleReceive(const std::string& message);
    void sendThread();
    void sendAll(const std::string& message, std::vector<std::shared_ptr<udp::endpoint>> &endpoints);
    void sendToClient(const std::string& message, udp::endpoint &client_t);
    udp::socket &Socket(){return socket_;}
    std::shared_ptr<EntityManager> &Entities(){return entityManagerPtr_;}
    // ------------CMD--------------
    void StartExec(const std::string& message, udp::endpoint &client);
    void sendPlayersPosition();
    void setPlayerPosition(Entity player);
    void setMobPosition(Entity player);
    void sendBulletPosition();
    // void sendProjectilsPosition();
    // void sendBotsPosition();
    // void sendPowerUpPosition();
    // void sendScores();
    std::vector<std::string> cmd_;
    std::array<char, 1024> recv_buf_;
private:
    unsigned short port_;
    udp::endpoint client = udp::endpoint();
    std::vector<std::shared_ptr<udp::endpoint>> remote_endpoints_;
    udp::socket socket_;
    std::shared_ptr<EntityManager> entityManagerPtr_;
    std::thread recv_thread_;
    std::thread send_thread_;
};