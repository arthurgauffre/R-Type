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
  /**
   * @brief A header for the network message.
   *
   * This member variable holds the header information for a network message.
   * The type of the header is a template class `MessageHeader` with a template
   * parameter `T`.
   */
  MessageHeader<T> header{};

  /**
   * @brief A vector to store the body of the network message.
   *
   * This vector holds the raw byte data (uint8_t) that constitutes the body of the network message.
   * It can be used to store any kind of binary data that needs to be transmitted over the network.
   */
  std::vector<uint8_t> body;

  /**
   * @brief Get the size of the message body.
   *
   * @return size_t The size of the message body.
   */
  size_t size() const { return body.size(); }

  /**
   * @brief Overloaded stream insertion operator for Message<T> class.
   *
   * This function allows a Message<T> object to be output to an ostream.
   * It outputs the message ID and size in the format "ID:<id> Size:<size>".
   *
   * @tparam T The type of the message.
   * @param os The output stream.
   * @param message The Message<T> object to be output.
   * @return A reference to the output stream.
   */
  friend std::ostream &operator<<(std::ostream &os, const Message<T> &message) {
    os << "ID:" << static_cast<int>(message.header.id)
       << " Size:" << message.header.size;
    return os;
  }

  /**
   * @brief Overloads the << operator to append data to the message body.
   *
   * This function template allows appending data of any standard layout type to the message body.
   * It ensures that the data type is simple enough to be copied directly into the message's internal
   * storage vector. The message body is resized to accommodate the new data, and the data is copied
   * into the newly allocated space. The message header's size is updated to reflect the new total size
   * of the message.
   *
   * @tparam DataType The type of data to be appended to the message body. Must be a standard layout type.
   * @param message The message object to which the data will be appended.
   * @param data The data to be appended to the message body.
   * @return A reference to the modified message object.
   *
   * @note This function uses static_assert to ensure that the DataType is a standard layout type.
   *       If the DataType is too complex, a compile-time error will be generated.
   */
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

  /**
   * @brief Extracts data from the message body and assigns it to the provided data variable.
   *
   * This operator function extracts a data element of type DataType from the message body,
   * assigns it to the provided data variable, and then resizes the message body accordingly.
   * It also updates the message header size to reflect the new size of the message.
   *
   * @tparam DataType The type of data to be extracted from the message body. Must be of standard layout.
   * @param message The message object from which data is to be extracted.
   * @param data The variable where the extracted data will be stored.
   * @return A reference to the modified message object.
   *
   * @note This function uses static_assert to ensure that DataType is of standard layout.
   *       If DataType is too complex, a compile-time error will be generated.
   */
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
