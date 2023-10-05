/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** TCPServer.hpp
*/

#pragma once
#include <boost/asio.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "TCPConnexion.hpp"
#include "../../Save/HandleSave.hpp"
#include "../../Room/RoomLobby.hpp"
#include <iostream>

class TCPServer {
public:
  TCPServer(boost::asio::io_context& io_context);
  void print_all_client_request();
  void getAllTcpRequest();
  // delete a lobbys
  bool deleteLobby(std::string uuid) {
    for (std::shared_ptr<RoomLobby> _lobby : _lobbys) {
      if (_lobby->getUuid() == uuid) {
        // _lobbys.erase(_lobby);
        return true;
      }
    }
    return false;
  };

  std::list <std::shared_ptr<PlayerLobby>> players_;
  HandleSave _save;
  std::vector <std::shared_ptr<RoomLobby>> _lobbys;
private:
  void start_accept();
  void handle_accept(TCPConnection::pointer new_connection, const boost::system::error_code& error);
  // std::list<TCPConnection::pointer>& Clients(){return clients_;}

protected:
  boost::asio::io_context& io_context_;
  boost::asio::ip::tcp::acceptor acceptor_;
  std::list<Request> requests_;
  // std::list<TCPConnection::pointer> clients_;
};