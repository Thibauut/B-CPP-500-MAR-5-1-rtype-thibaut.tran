#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
using boost::asio::ip::udp;

int main()
{
	try {
		boost::asio::io_service io_service;

		udp::endpoint receiver_endpoint (boost::asio::ip::address::from_string("192.168.0.30"), 35265);
		udp::socket socket(io_service);
		socket.open(udp::v4());
        for (;;) {
			std::string request;
			std::getline(std::cin, request);
			boost::array<char, 1024> send_buf  = {0};
			socket.send_to(boost::asio::buffer(request), receiver_endpoint);
            boost::array<char, 128> recv_buf;
			// std::cout << request << std::endl;
			std::fill(recv_buf.begin(),recv_buf.end(), 0);
            udp::endpoint sender_endpoint;
            size_t len = socket.receive_from(boost::asio::buffer(recv_buf), sender_endpoint);
            std::cout << recv_buf.data() << std::endl;
        }
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	boost::asio::io_service io_service;
	return 0;
}