#include "TCPConnexion.hpp"

TCPConnection::pointer TCPConnection::create(boost::asio::io_context& io_context)
{
  return pointer(new TCPConnection(io_context));
}

TCPConnection::TCPConnection(boost::asio::io_context& io_context)
  : socket_(io_context)
{
  _uuid = boost::uuids::random_generator()();
}

void TCPConnection::start()
{
  message_ = "Welcome to Hess-Type server !\n";

  boost::asio::async_write(socket_, boost::asio::buffer(message_),
      [shared_this = shared_from_this()](const boost::system::error_code& error,
                                          size_t bytes_transferred) {
        shared_this->handle_write(error, bytes_transferred);
      });
}

void TCPConnection::do_read() {
  socket_.async_read_some(boost::asio::buffer(data_),
      [shared_this = shared_from_this()](const boost::system::error_code& error,
                                          size_t bytes_transferred) {
        shared_this->handle_read(error, bytes_transferred);
      });
}

void TCPConnection::send(std::string &message)
{
    socket_.async_write_some(boost::asio::buffer(message),
        [myMessage = message](const boost::system::error_code& error,
                                            size_t bytes_transferred) {
          std::cout << "-> " << myMessage << std::endl;
        });
}

void TCPConnection::do_write()
{
  //  std::cout << socket_. << "\n";
  socket_.async_write_some(boost::asio::buffer("bien reçu\n"),
      [shared_this = shared_from_this()](const boost::system::error_code& error,
                                          size_t bytes_transferred) {
        shared_this->handle_write(error, bytes_transferred);
      });
}

void TCPConnection::handle_read(const boost::system::error_code& error, size_t bytes_transferred)
{
  if (!error)
  {
    std::string data = std::string(data_.begin(), data_.begin() + bytes_transferred);
    if (!data.empty()) {
        Request new_request(data, socket(), _uuid);
        requests_.push_back(new_request);
        int i = 0;
        for (const Request& request : requests_) {
          i++;
        }
    }
    do_read();
  } else {
    socket_.close();
  }
}

void TCPConnection::handle_write(const boost::system::error_code& /*error*/,
                                 size_t /*bytes_transferred*/)
{
  do_read();
}