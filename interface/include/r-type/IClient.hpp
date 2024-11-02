/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** IClient
*/

#ifndef ICLIENT_HPP_
#define ICLIENT_HPP_

#pragma once

#include <NetworkConnection.hpp>
#include <NetworkQueue.hpp>
#include <NetworkingCommon.hpp>

namespace rtype {
namespace network {
template <typename T> class IClient {
public:
  /**
   * @brief Construct a new IClient object.
   */
  IClient() {}

  /**
   * @brief Virtual destructor for the IClient interface.
   *
   * This ensures that derived class destructors are called properly
   * when an object is deleted through a pointer to IClient.
   */
  virtual ~IClient() {}

  /**
   * @brief Establishes a connection to the specified host and port.
   *
   * @param host The hostname or IP address of the server to connect to.
   * @param port The port number on the server to connect to.
   * @return true if the connection was successfully established, false otherwise.
   */
  virtual bool Connect(const std::string &host, const uint16_t port) = 0;

  /**
   * @brief Disconnects the client from the server.
   *
   * This function is responsible for terminating the connection between the client and the server.
   * It should be implemented to handle any necessary cleanup and ensure that the client is properly
   * disconnected.
   */
  virtual void Disconnect() = 0;

  /**
   * @brief Check if the client is connected.
   *
   * This function checks the connection status of the client.
   *
   * @return true if the client is connected, false otherwise.
   */
  virtual bool IsConnected() = 0;

  /**
   * @brief Sends a message to the client.
   *
   * This function is responsible for sending a message of type T to the client.
   * It is a pure virtual function, meaning it must be implemented by any derived class.
   *
   * @param message The message to be sent to the client.
   */
  virtual void Send(const rtype::network::Message<T> &message) = 0;

  /**
   * @brief Pure virtual function to retrieve the queue of incoming messages.
   *
   * This function returns a reference to a ServerQueue containing OwnedMessage objects.
   * The template parameter T represents the type of the message.
   *
   * @tparam T The type of the message.
   * @return A reference to a ServerQueue containing OwnedMessage objects.
   */
  virtual rtype::network::ServerQueue<rtype::network::OwnedMessage<T>> &GetIncomingMessages() = 0;
};
} // namespace network
} // namespace rtype

#endif /* !ICLIENT_HPP_ */
