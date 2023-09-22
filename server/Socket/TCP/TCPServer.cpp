#include "TCPServer.hpp"

TCPServer::TCPServer(boost::asio::io_context& io_context)
    : io_context_(io_context),
      acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 12345))
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
    std::cout << "<- NEW CLIENT" << std::endl;
    new_connection->start();
    Clients().push_back(new_connection);
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

void TCPServer::getAllTcpRequest(HandleSave &save, std::vector <RoomLobby> &_lobbys) {
  for (TCPConnection::pointer &client : clients_) {
    requests_.splice(requests_.end(), client->requests());
  }

  int i = 0;
  for (Request req : requests_) {
    i++;
    std::cout << "<= " << req._data << std::endl;
    Parser pars = Parser(req, save, _lobbys);
  }
  requests_.clear();
}