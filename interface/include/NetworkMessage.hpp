/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** NetworkMessage
*/

#ifndef NETWORKMESSAGE_HPP_
#define NETWORKMESSAGE_HPP_

#include <NetworkConnection.hpp>
#include <iostream>

namespace rtype {
namespace network {
/**
 * @brief A template structure representing the header of a network message.
 *
 * @tparam T The type of the message identifier.
 */
template <typename T> struct MessageHeader {
  T id{};
  uint32_t size = 0;
};

/**
 * @brief A templated structure representing a network message.
 *
 * This structure encapsulates a message header and a body, providing
 * functionalities to manipulate the message content and size.
 *
 * @tparam T The type of the message header.
 */
template <typename T> struct Message {
  MessageHeader<T> header{};
  std::vector<uint8_t> body;

  size_t size() const { return body.size(); }

  friend std::ostream &operator<<(std::ostream &os, const Message<T> &message) {
    os << "ID:" << static_cast<int>(message.header.id)
       << " Size:" << message.header.size;
    return os;
  }

  template <typename DataType>
  friend Message<T> &operator<<(Message<T> &message, const DataType &data) {
    static_assert(std::is_standard_layout<DataType>::value,
                  "Data is too complex to be pushed into vector");

    size_t i = message.body.size();
    message.body.resize(message.body.size() + sizeof(DataType));
    std::memcpy(message.body.data() + i, &data, sizeof(DataType));
    message.header.size = message.size();
    return message;
  }

  template <typename DataType>
  friend Message<T> &operator>>(Message<T> &message, DataType &data) {
    static_assert(std::is_standard_layout<DataType>::value,
                  "Data is too complex to be pushed into vector");

    size_t i = message.body.size() - sizeof(DataType);
    std::memcpy(&data, message.body.data() + i, sizeof(DataType));
    message.body.resize(i);
    message.header.size = message.size();
    return message;
  }
};
} // namespace network
} // namespace rtype
#endif /* !NETWORKMESSAGE_HPP_ */
