/*
** EPITECH PROJECT, 2023
** client
** File description:
** Client
*/

#pragma once
    #include <iostream>
    #include <boost/asio.hpp>
    // #include <queue>
    #include <mutex>
    #include <condition_variable>
    #include <boost/array.hpp>
    #include <atomic>
    #include "../ThreadHandler/ThreadHandler.hpp"
    #include <boost/asio.hpp>
    #include <boost/bind.hpp>

class ClientConnectionTCP : public ThreadHandler {
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
        void JoinRoom();
        void Ready();
        void LeaveRoom();
        void DeleteRoom();


        std::string ip_;
        std::string port_;
        std::string username_;
        std::string uuid_;
        boost::asio::streambuf buffer_;
        std::mutex responseMutex;
        std::string response_;
        boost::asio::io_service ioService;
        boost::asio::ip::tcp::socket socket_;

        std::string infoName_;
        std::string infoLevel_;
        std::string infoRoomUuid_;

//         std::queue<std::string> sendMessageQueue_;
//         std::mutex messageMutex_;
//         std::condition_variable messageCondition_;
//         bool sending_;
};
