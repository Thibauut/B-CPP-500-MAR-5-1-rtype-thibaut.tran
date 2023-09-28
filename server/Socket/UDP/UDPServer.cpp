/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** udpTest.cpp
*/

#include "UDPServer.hpp"

UDPServer::UDPServer(boost::asio::io_service& io_service, unsigned short port)
    : socket_(io_service, udp::endpoint(udp::v4(), port)) {
        recv_buf_.resize(1024);
        StartReceive();
}

void UDPServer::StartReceive() {
    socket_.async_receive_from(
    boost::asio::buffer(recv_buf_), remote_endpoint_,
    [this](const boost::system::error_code& error, std::size_t bytes_received) {
        if (!error || error == boost::asio::error::message_size) {
            std::string message(recv_buf_.begin(), recv_buf_.begin() + bytes_received);
            StartSend(message);
            StartReceive();
        } else {
            std::cerr << "Receive error: " << error.message() << std::endl;
        }
    });
}

void UDPServer::StartSend(const std::string& message){
    socket_.async_send_to(
        boost::asio::buffer(message), remote_endpoint_,
        [this](const boost::system::error_code& error, std::size_t bytes_sent) {
            if (error) {
                std::cerr << "Send error: " << error.message() << std::endl;
            }
        });
}
int main()
{
	boost::asio::io_service io_service;
	UDPServer server(io_service, 1234);
	io_service.run();
	return 0;
}