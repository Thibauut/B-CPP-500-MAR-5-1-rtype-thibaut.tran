#include "testserv.hpp"

int main()
{
    boost::asio::io_service io_service;
    UDPServer server(io_service, 7171);
    return 0;
}
