/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** OwnedMessage
*/

#ifndef OWNEDMESSAGE_HPP_
#define OWNEDMESSAGE_HPP_

#include <server/NetworkMessage.hpp>
#include <server/NetworkingCommon.hpp>

namespace rtype {
namespace network {
template <typename T> class NetworkConnection;
template <typename T> struct OwnedMessage {
  std::shared_ptr<NetworkConnection<T>> remoteConnection;
  Message<T> message;

  friend std::ostream &operator<<(std::ostream &os,
                                  const OwnedMessage<T> &message) {
    os << message.message;
    return os;
  }
};
} // namespace network
} // namespace rtype

#endif /* !OWNEDMESSAGE_HPP_ */
