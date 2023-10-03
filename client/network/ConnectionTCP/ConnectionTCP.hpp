/*
** EPITECH PROJECT, 2023
** client
** File description:
** Client
*/

#pragma once
    #include <iostream>
    #include <boost/asio.hpp>
    #include <mutex>
    #include <condition_variable>
    #include <boost/array.hpp>
    #include <atomic>
    #include "../ThreadHandler/ThreadHandler.hpp"
    #include <boost/asio.hpp>
    #include <boost/bind.hpp>

std::atomic<bool> shouldStop(false);

class ClientConnectionTCP : public ThreadHandler {
    struct Room {
        std::string name;
        std::string slot;
        std::string uuid;
    };

    struct Player {
        std::string name;
        std::string level;
    };

    public:
        ClientConnectionTCP(const std::string&, const std::string&, const std::string&);
        void setMessage(const std::string&);
        void run() override;
        bool getRunning() override;
        std::string message_;
        boost::asio::io_service& getService();
        boost::asio::ip::tcp::socket& getSocket();

        bool sendMessage(const std::string&);
        void readMessage();
        void handleRead(const boost::system::error_code&, std::size_t);
        void Login();
        std::string extractArguments(const std::string&input, const std::string& keyword);
        void Disconnect();
        void GetPlayerInfo();
        void CreateRoom(std::string roomName, std::string roomSize);
        std::string JoinRoom(std::string roomuuid , std::string playeruuid);
        bool Ready(std::string roomuuid, std::string playeruuid, std::string& startId, std::string& portUdp);
        void LeaveRoom(std::string roomuuid);
        void DeleteRoom(std::string roomuuid);
        void GetRoomInfo(std::string roomuuid);
        void GetRoomList();


        std::string ip_;
        std::string port_;
        std::string username_;
        std::string uuid_;

        std::mutex mutex_;

        std::string portUdp_;
        boost::asio::streambuf buffer_;
        std::mutex responseMutex;
        std::string response_;
        boost::asio::io_service ioService;
        boost::asio::ip::tcp::socket socket_;

        std::string infoName_;
        std::string infoLevel_;
        std::string infoRoomUuid_;

        std::vector<Room *> rooms;
        std::vector<Player *> players;

        std::string token;
        bool startGame = false;
        bool readyGame_;

//         std::queue<std::string> sendMessageQueue_;
//         std::mutex messageMutex_;
//         std::condition_variable messageCondition_;
//         bool sending_;
};
