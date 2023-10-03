#include "testserv.hpp"

int main()
{
    boost::asio::io_service io_service;
    UDPServer server(io_service, 8914);
    return 0;
}
