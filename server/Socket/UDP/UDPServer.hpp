#pragma once

#include <array>
#include <boost/asio.hpp>
#include <thread>
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
            std::cout << "false" << std::endl;
            return false;
        }
        for (udp::endpoint tmp : remote_endpoints_) {
            if (tmp.address() == client.address()) {
                std::cout << "true" << std::endl;
                return true;
            }
        }
        std::cout << "false" << std::endl;
        return false;
    }
    void StartReceive();
    void handleReceive(const std::string& message);
    void sendThread();
    void sendAll(const std::string& message, std::vector<udp::endpoint> &endpoints);
    void sendToClient(const std::string& message, udp::endpoint &client_t);
    udp::socket &Socket(){return socket_;}
    std::shared_ptr<EntityManager> &Entities(){return entityManagerPtr_;}
    // ------------CMD--------------
    void StartExec(const std::string& message, udp::endpoint &client);
    void sendPlayersPosition();
    void setPlayerStatus(int id, int x, int y, std::string shoot);
    // void sendProjectilsPosition();
    // void sendBotsPosition();
    // void sendPowerUpPosition();
    // void sendScores();
    std::vector<std::string> cmd_;
    std::array<char, 1024> recv_buf_;
private:
    unsigned short port_;
    udp::endpoint client = udp::endpoint();
    std::vector<udp::endpoint> remote_endpoints_;
    udp::socket socket_;
    std::shared_ptr<EntityManager> entityManagerPtr_;
    std::thread recv_thread_;
    std::thread send_thread_;
};