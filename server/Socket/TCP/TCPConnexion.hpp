#ifndef TCPConnection_HPP
#define TCPConnection_HPP

#include <boost/asio.hpp>
using boost::asio::ip::tcp;

class TCPConnection : public std::enable_shared_from_this<TCPConnection>
{
public:
  typedef std::shared_ptr<TCPConnection> pointer;

  static pointer create(boost::asio::io_context& io_context);
     tcp::socket& socket()
  {
    return socket_;
  }
  void start();

private:
  TCPConnection(boost::asio::io_context& io_context);
  void do_read();
  void do_write();
  void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
  void handle_write(const boost::system::error_code& error, size_t bytes_transferred);

  boost::asio::ip::tcp::socket socket_;
  std::string message_;
  std::array<char, 1024> data_;
};

#endif // TCPConnection_HPP
