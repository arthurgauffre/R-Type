/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** NetworkConnection
*/

#ifndef NETWORKCONNECTION_HPP_
#define NETWORKCONNECTION_HPP_

#include <NetworkQueue.hpp>
#include <OwnedMessage.hpp>

namespace rtype {
namespace network {
template <typename T> class Server;
template <typename T>
class NetworkConnection
    : public std::enable_shared_from_this<NetworkConnection<T>> {
public:
  enum class actualOwner {
    SERVER,
    CLIENT
  }

  NetworkConnection(actualOwner owner, asio::io_context &asioContext,
                    asio::ip::udp::socket socket,
                    rtype::network::ServerQueue<rtype::network::OwnedMessage<T>>
                        &incomingMessages) : {}

protected:
  asio::ip::udp::socket asioSocket;
  asio::ip::udp::endpoint endpoint;

  asio::io_context &asioContext;
};
} // namespace network
} // namespace rtype

#endif /* !NETWORKCONNECTION_HPP_ */
