#include "TCPServer.hpp"

TCPServer::TCPServer(boost::asio::io_context& io_context)
    : io_context_(io_context),
      acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 4000))
{
  start_accept();
}

void TCPServer::start_accept()
{
  TCPConnection::pointer new_connection = TCPConnection::create(io_context_);
  acceptor_.async_accept(new_connection->socket(),
      [this, new_connection](const boost::system::error_code& error) {
        handle_accept(new_connection, error);
      });
}

void TCPServer::handle_accept(TCPConnection::pointer new_connection, const boost::system::error_code& error)
{
  if (!error)
  {
    new_connection->start();
    Clients().push_back(new_connection);
    print_all_client_request();
  }

  start_accept();
}

  void TCPServer::print_all_client_request() {
        std::cout<< "all request:"<<std::endl;
       int i = 1, j = 1;
        for (TCPConnection::pointer client : clients_) {
              std::cout<< "client  " << i << " :"<<std::endl;
            for (Request &request : client->requests()) {
              std::cout<< "        res " << j << " = "<< request._data <<std::endl;
              j++;
            }
            i++, j = 1;
        }
  }