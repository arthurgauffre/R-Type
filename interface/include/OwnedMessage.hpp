/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** OwnedMessage
*/

#ifndef OWNEDMESSAGE_HPP_
#define OWNEDMESSAGE_HPP_

#include <NetworkMessage.hpp>
#include <NetworkingCommon.hpp>

namespace rtype {
namespace network {
template <typename T> class NetworkConnection;
template <typename T> struct OwnedMessage {
  /**
   * @brief A shared pointer to a NetworkConnection object.
   *
   * This shared pointer manages the lifetime of a NetworkConnection object,
   * ensuring that the object is properly deleted when no longer in use.
   *
   * @tparam T The type of data that the NetworkConnection handles.
   */
  std::shared_ptr<NetworkConnection<T>> remoteConnection = nullptr;

  /**
   * @brief Represents a message owned by a specific entity in the R-Type network.
   *
   * This template class encapsulates a message of type T, which is used for
   * communication within the R-Type network. The message can contain various
   * types of data depending on the template parameter T.
   *
   * @tparam T The type of data contained in the message.
   */
  rtype::network::Message<T> message;

  /**
   * @brief Overloaded stream insertion operator for OwnedMessage.
   *
   * This friend function allows an OwnedMessage object to be inserted into an
   * output stream. It outputs the message contained within the OwnedMessage.
   *
   * @tparam T The type of the message.
   * @param os The output stream to insert the message into.
   * @param message The OwnedMessage object containing the message to be inserted.
   * @return A reference to the output stream.
   */
  friend std::ostream &operator<<(std::ostream &os,
                                  const OwnedMessage<T> &message) {
    os << message.message;
    return os;
  }
};
} // namespace network
} // namespace rtype

#endif /* !OWNEDMESSAGE_HPP_ */
