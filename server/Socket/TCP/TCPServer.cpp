#include "TCPServer.hpp"
#include "HandleRequest/Parser.hpp"

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
  if (!error) {
    std::cout << "<- NEW CLIENT" << std::endl;
    new_connection->start();
    players_.push_back(std::make_shared<PlayerLobby>(new_connection));
    // Clients().push_back(new_connection);
  }
  start_accept();
}

  void TCPServer::print_all_client_request() {
        std::cout<< "all request:"<<std::endl;
       int i = 1, j = 1;
        // for (TCPConnection::pointer client : clients_) {
        //       std::cout<< "client  " << i << " :"<<std::endl;
        //     for (Request &request : client->requests()) {
        //       std::cout<< "        res " << j << " = "<< request._data <<std::endl;
        //       j++;
        //     }
        //     i++, j = 1;
        // }
  }

void TCPServer::getAllTcpRequest() {
  for (std::shared_ptr<PlayerLobby> player : players_) {
    requests_.splice(requests_.end(), player.get()->connection.get()->requests());
  }

  for (std::shared_ptr<RoomLobby> room : _lobbys) {
    if (room.get()->getNbReadyPlayers() == room.get()->getNbSlots() && !room.get()->isStarted()) {
      room.get()->startGame();
      for (int i = 0; i < room.get()->getPlayers().size(); i++) {
              std::string response = "START\n";
              room.get()->getPlayers().at(i).get()->getSocket().async_write_some(boost::asio::buffer(response),
              [message = response](const boost::system::error_code& error,
              size_t bytes_transferred) { std::cout << "-> " << message; });
          }
      }
  }
  int i = 0;
  for (Request req : requests_) {
    i++;
    std::cout << "<- " << req._data;
    Parser pars = Parser(req, this);
  }
  requests_.clear();
}