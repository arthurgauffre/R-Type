/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AClient
*/

#ifndef ACLIENT_HPP_
#define ACLIENT_HPP_

#pragma once

#include <Error.hpp>
#include <r-type/IClient.hpp>

namespace rtype {
namespace network {
template <typename T> class AClient : virtual public IClient<T> {
public:
  /**
   * @brief Default constructor for the AClient class.
   */
  AClient() {}

  /**
   * @brief Destructor for the AClient class.
   *
   * This destructor ensures that the client is disconnected properly
   * by calling the Disconnet() method.
   */
  virtual ~AClient() { Disconnet(); }

  /**
   * @brief Establishes a connection to a remote server.
   *
   * This function attempts to connect to a remote server using the provided
   * host address and port number. It creates a UDP socket and initializes
   * a NetworkConnection object to manage the connection. If the connection
   * is successfully established, a separate thread is started to run the
   * ASIO context.
   *
   * @param host The IP address or hostname of the remote server.
   * @param port The port number on the remote server to connect to.
   * @return true if the connection is successfully established, false otherwise.
   */
  bool Connect(const std::string &host, const uint16_t port) {
    try {
      asio::ip::udp::endpoint remoteEndpoint =
          asio::ip::udp::endpoint(asio::ip::address::from_string(host), port);
      asio::ip::udp::socket socket(
          asioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0));
      connection = std::make_shared<NetworkConnection<T>>(
          NetworkConnection<T>::actualOwner::CLIENT, asioContext,
          std::move(socket), std::move(remoteEndpoint),
          queueOfincomingMessages);
      connection->EstablishServerConnection();
      contextThread = std::thread([this]() { asioContext.run(); });

    } catch (rtype::ClientConnectionException &e) {
      std::cerr << "Client connection failed : " << e.what() << std::endl;
      return false;
    }
    return true;
  }

  /**
   * @brief Disconnects the client from the server.
   *
   * This function checks if the client is currently connected to the server.
   * If connected, it disconnects the client, stops the ASIO context, joins the context thread if it is joinable,
   * and resets the connection.
   */
  void Disconnet() {
    if (IsConnected())
      connection->Disconnect();
    asioContext.stop();
    if (contextThread.joinable())
      contextThread.join();
    connection.reset();
  }

  /**
   * @brief Checks if the client is connected.
   *
   * This function checks the connection status of the client. If the connection
   * object exists, it returns the result of the connection's IsConnected method.
   * Otherwise, it returns false.
   *
   * @return true if the client is connected, false otherwise.
   */
  bool IsConnected() {
    if (connection)
      return connection->IsConnected();
    else
      return false;
  }

  /**
   * @brief Sends a message through the network connection if it is connected.
   *
   * @tparam T The type of the message to be sent.
   * @param message The message to be sent.
   */
  void Send(const rtype::network::Message<T> &message) {
    if (IsConnected())
      connection->Send(message);
  }

  /**
   * @brief Retrieves the queue of incoming messages.
   *
   * This function returns a reference to the queue that holds the incoming messages
   * for the client. The queue contains messages that have been received from the server.
   *
   * @return ServerQueue<OwnedMessage<T>>& Reference to the queue of incoming messages.
   */
  ServerQueue<OwnedMessage<T>> &GetIncomingMessages() {
    return queueOfincomingMessages;
  }

  /**
   * @brief Retrieves the network connection.
   *
   * This function returns a constant reference to a unique pointer that holds the network connection.
   *
   * @tparam T The type of the network connection.
   * @return const std::unique_ptr<NetworkConnection<T>>& A constant reference to the unique pointer containing the network connection.
   */
  const std::unique_ptr<NetworkConnection<T>> &GetConnection() {
    return connection;
  }

protected:
  /**
   * @brief The io_context class provides core I/O functionality for asynchronous operations.
   *
   * The io_context object is used to initiate asynchronous operations such as network communication.
   * It is responsible for dispatching handlers for asynchronous operations and managing the event loop.
   *
   * @see https://www.boost.org/doc/libs/1_75_0/doc/html/boost_asio/reference/io_context.html
   */
  asio::io_context asioContext;

  /**
   * @brief Thread object to handle the context operations.
   *
   * This thread is responsible for managing and executing context-related tasks
   * in a concurrent manner, allowing for parallel processing and improved performance.
   */
  std::thread contextThread;

  /**
   * @brief A shared pointer to a NetworkConnection object.
   *
   * This member holds a shared pointer to a NetworkConnection object of type T.
   * It is used to manage the connection within the R-Type client interface.
   * The shared pointer ensures that the NetworkConnection object is properly
   * managed and deallocated when no longer in use.
   *
   * @tparam T The type of the NetworkConnection.
   */
  std::shared_ptr<rtype::network::NetworkConnection<T>> connection;

private:
  /**
   * @brief A queue that holds incoming messages from the server.
   *
   * This member variable is a ServerQueue that stores OwnedMessage objects
   * of type T. It is used to manage and process messages received from the server.
   */
  ServerQueue<OwnedMessage<T>> queueOfincomingMessages;
};
} // namespace network
} // namespace rtype

#endif /* !ACLIENT_HPP_ */
