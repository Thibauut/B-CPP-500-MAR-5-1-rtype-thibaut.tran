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
    // #include <mutex>
    #include <condition_variable>
    #include <boost/array.hpp>
    #include "../ThreadHandler/ThreadHandler.hpp"

class ClientConnectionTCP : public ThreadHandler {
    public:
        ClientConnectionTCP(const std::string&, const std::string&, const std::string&);
        void setMessage(const std::string&);
        void run() override;
        bool getRunning() override;
        std::string message_;
        boost::asio::io_service& getService();
        boost::asio::ip::tcp::socket& getSocket();
        void Login();
        std::string uuid_;
        std::string ip_;
        std::string port_;
        std::string username_;
    protected:
    private:
        boost::asio::io_service ioService;
        boost::asio::ip::tcp::socket socket_;
        bool sendMessage(const std::string&);
        std::string readMessage();
//         std::queue<std::string> sendMessageQueue_;
//         std::mutex messageMutex_;
//         std::condition_variable messageCondition_;
//         bool sending_;
};
