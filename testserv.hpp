#pragma once

#include <boost/asio.hpp>
#include <iostream>
using boost::asio::ip::udp;

class UDPServer {
public:
    UDPServer(boost::asio::io_service& io_service, unsigned short port)
        : socket_(io_service, udp::endpoint(udp::v4(), port)) {
            try {
                int newX = 300;
                int newY = 200;
                int newX2 = 500;
                int newY2 = 200;
                std::string message = "";
                message = "1 " + std::to_string(newX) + " " +  std::to_string(newY) + " 2 " + std::to_string(newX2) + " " +  std::to_string(newY2) + "\n";
                while (1)
                {
                    std::vector<char> recv_buf(1024);
                    udp::endpoint remote_endpoint;
                    boost::system::error_code error;
                    socket_.receive_from(boost::asio::buffer(recv_buf), remote_endpoint, 0, error);
                    if (error && error != boost::asio::error::message_size)
                        throw boost::system::system_error(error);
                    boost::system::error_code ignored_error;
                    // std::cout << recv_buf.data() << std::endl;

                    std::string recv_str(recv_buf.data(), recv_buf.size());
                    if (recv_str.find("1 LEFT") != std::string::npos) {
                        newX -= 1;
                        message = "1 " + std::to_string(newX) + " " +  std::to_string(newY) + "\n";
                    }
                    if (recv_str.find("1 RIGHT") != std::string::npos) {
                        newX += 1;
                        message = "1 " + std::to_string(newX) + " " +  std::to_string(newY) + "\n";

                    }
                    if (recv_str.find("1 UP") != std::string::npos) {
                        std::cout << "UP" << std::endl;
                        newY -= 1;
                        message = "1 " + std::to_string(newX) + " " +  std::to_string(newY) + "\n";
                    }
                    if (recv_str.find("1 DOWN") != std::string::npos) {
                        newY += 1;
                        message = "1 " + std::to_string(newX) + " " +  std::to_string(newY) + "\n";
                    }
                    socket_.send_to(boost::asio::buffer(message), remote_endpoint, 0, ignored_error);
                    message = "";
                }
            } catch (std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
        }
private:
    udp::socket socket_;
};