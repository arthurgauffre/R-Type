/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** NetworkMessage
*/

#ifndef NETWORKMESSAGE_HPP_
#define NETWORKMESSAGE_HPP_

namespace rtype {
namespace network {
template <typename T> struct MessageHeader {
  T id{};
  uint32_t size = 0;
};

template <typename T> struct Message {
  MessageHeader<T> header{};
  std::vector<uint8_t> body;

  size_t size() const { return body.size(); }
};
} // namespace network
} // namespace rtype
#endif /* !NETWORKMESSAGE_HPP_ */
