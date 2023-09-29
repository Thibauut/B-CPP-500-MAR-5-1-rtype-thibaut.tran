#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <list>
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
    UDPServer(boost::asio::io_service& io_service, unsigned short port, std::shared_ptr<EntityManager> entity_manager);
    void StartReceive();
    void StartSend(const std::string& message);
    udp::socket &Socket(){return socket_;}
    std::shared_ptr<EntityManager> &Entitys(){return entityManagerPtr_;}
    void StartExec(const std::string& message);
    // ------------CMD--------------
    void SendAllPlayersPosition();
    void SendAllProjectilsPosition();
    void SendAllPnjPosition();
    void SendAllCollectiblesPosition();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void Shoot();
    void sendScores();
    std::vector<std::string> cmd_;

private:
    udp::endpoint remote_endpoint_;
    std::vector<char> recv_buf_;
    udp::socket socket_;
    std::shared_ptr<EntityManager> entityManagerPtr_;
};