/*
** EPITECH PROJECT, 2023
** client
** File description:
** Client
*/

#pragma once
    #include <iostream>
    #include <boost/asio.hpp>
    #include <boost/array.hpp>
    #include <boost/serialization/vector.hpp>
    #include <boost/serialization/shared_ptr.hpp>
    #include <boost/archive/binary_oarchive.hpp>
    #include <boost/archive/binary_iarchive.hpp>
    #include <boost/serialization/export.hpp>
    #include "../ThreadHandler/ThreadHandler.hpp"
    #include "../../../GameEngine/Components/Sprite/Sprite.hpp"
    #include "../../../GameEngine/GameEngine.hpp"

class ClientOpenUDP : public ThreadHandler {
    public:

        struct PlayersPos {
            int id;
            int posX;
            int posY;
        };

        struct PlayerPosition {
            int posX;
            int posY;
        };

        ClientOpenUDP(const std::string& serverIp, const std::string& serverPort, std::vector<std::shared_ptr<Entity>> &playersEntity, const std::string my_id);
        void setMessage(const std::string&);
        void run() override;

        bool sendMessageSync(const std::string&);

        bool readMessageGlobal();

        std::string serialize(std::shared_ptr<Entity> entity);

        Entity deserialize(std::string serializedData);

        bool getRunning() override;

        std::string ipAddress_;
        std::string udpPort_;
        std::string udpAddress_;
        std::string message_;
        std::string my_id_;

        boost::array<char, 128>  buffer_;
        boost::asio::io_context ioService;
        boost::asio::ip::udp::socket socket_;
        boost::asio::ip::udp::endpoint endpoint_;

        bool is1 = false;
        bool is2 = false;
        bool is3 = false;
        bool is4 = false;

        // std::vector<std::shared_ptr<PlayerUDP>> &players_;

        std::vector<std::shared_ptr<Entity>> &playersEntity_;


        std::vector<std::shared_ptr<PlayersPos>> playersPos_;

        std::map<int, PlayerPosition> playerPositions;
};
