/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AClient
*/

#ifndef ACLIENT_HPP_
#define ACLIENT_HPP_

#pragma once

// #include <NetworkConnection.hpp>
#include <Error.hpp>
// #include <NetworkingCommon.hpp>
// #include <OwnedMessage.hpp>
#include <r-type/IClient.hpp>

namespace rtype {
namespace network {
template <typename T> class AClient : virtual public IClient<T> {
public:
  AClient() {}
  virtual ~AClient() { Disconnet(); }

  bool Connect(const std::string &host, const uint16_t port) {
    try {
      asio::ip::udp::endpoint remoteEndpoint =
          asio::ip::udp::endpoint(asio::ip::address::from_string(host), port);
      asio::ip::udp::socket socket(
          asioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0));
      connection = std::make_unique<NetworkConnection<T>>(
          NetworkConnection<T>::actualOwner::CLIENT, asioContext,
          std::move(socket), std::move(remoteEndpoint),
          queueOfincomingMessages);
      connection->EstablishServerConnection();
      // std::cout << "Connection : " << *(connection.get()) << std::endl;
      contextThread = std::thread([this]() { asioContext.run(); });

    } catch (rtype::ClientConnectionException &e) {
      std::cerr << "Client connection failed : " << e.what() << std::endl;
      return false;
    }
    return true;
  }

  void Disconnet() {
    if (IsConnected())
      connection->Disconnect();
    asioContext.stop();
    if (contextThread.joinable())
      contextThread.join();
    connection.release();
  }

  bool IsConnected() {
    if (connection)
      return connection->IsConnected();
    else
      return false;
  }

  void Send(const rtype::network::Message<T> &message) {
    if (IsConnected())
      connection->Send(message);
  }

  ServerQueue<OwnedMessage<T>> &GetIncomingMessages() {
    return queueOfincomingMessages;
  }

  const std::unique_ptr<NetworkConnection<T>> &GetConnection() {
    return connection;
  }

protected:
  asio::io_context asioContext;
  std::thread contextThread;
  std::unique_ptr<rtype::network::NetworkConnection<T>> connection;

private:
  ServerQueue<OwnedMessage<T>> queueOfincomingMessages;
};
} // namespace network
} // namespace rtype

#endif /* !ACLIENT_HPP_ */
