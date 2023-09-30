#pragma once
#include "TCPRequest.hpp"
#include <boost/asio.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <iostream>
#include <list>

using boost::asio::ip::tcp;

class TCPConnection : public std::enable_shared_from_this<TCPConnection>
{
public:
  typedef std::shared_ptr<TCPConnection> pointer;

  static pointer create(boost::asio::io_context& io_context);
  tcp::socket& socket(){return socket_;}
  std::list<Request>& requests(){return requests_;}
  void send(std::string &message);
  boost::uuids::uuid uuid(){return _uuid;}
  void start();

private:
  TCPConnection(boost::asio::io_context& io_context);
  void do_write();
  void do_read();
  void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
  void handle_write(const boost::system::error_code& error, size_t bytes_transferred);

  boost::asio::ip::tcp::socket socket_;
  boost::uuids::uuid _uuid;
  std::string message_;
  std::array<char, 1024> data_;
  std::list<Request> requests_;
};
