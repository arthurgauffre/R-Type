/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** NetworkConnection
*/

#ifndef NETWORKCONNECTION_HPP_
#define NETWORKCONNECTION_HPP_

#pragma once

#include <NetworkMessagesCommunication.hpp>
#include <NetworkQueue.hpp>
#include <OwnedMessage.hpp>
#include <r-type/IServer.hpp>

/**
 * @brief Overloads the << operator to output the local endpoint address and port of a UDP socket.
 *
 * This function allows you to use the << operator to print the local endpoint
 * address and port of an asio::ip::udp::socket object to an output stream.
 *
 * @param os The output stream to which the socket information will be written.
 * @param socket The UDP socket whose local endpoint address and port will be output.
 * @return A reference to the output stream after the socket information has been written.
 */
std::ostream &operator<<(std::ostream &os,
                         const asio::ip::udp::socket &socket) {
  os << socket.local_endpoint().address().to_string() << ":"
     << socket.local_endpoint().port();
  return os;
}

/**
 * @brief Overloads the stream insertion operator to output an asio::ip::udp::endpoint.
 *
 * This function allows an asio::ip::udp::endpoint to be output to an ostream
 * in the format "address:port".
 *
 * @param os The output stream to which the endpoint will be written.
 * @param endpoint The UDP endpoint to be written to the output stream.
 * @return A reference to the output stream.
 */
std::ostream &operator<<(std::ostream &os,
                         const asio::ip::udp::endpoint &endpoint) {
  os << endpoint.address().to_string() << ":" << endpoint.port();
  return os;
}

namespace rtype {
namespace network {
template <typename T> class IServer;
template <typename T>
class NetworkConnection
    : public std::enable_shared_from_this<NetworkConnection<T>> {
public:
  /**
   * @enum actualOwner
   * @brief Enum to represent the owner of the network connection.
   *
   * This enum is used to distinguish between the server and client
   * in a network connection context.
   *
   * @var actualOwner::SERVER
   * Represents the server as the owner of the network connection.
   *
   * @var actualOwner::CLIENT
   * Represents the client as the owner of the network connection.
   */
  enum class actualOwner { SERVER, CLIENT };

  /**
   * @brief Constructs a new NetworkConnection object.
   *
   * @param owner The owner type of the connection (SERVER or CLIENT).
   * @param otherAsioContext The io_context object used for asynchronous operations.
   * @param socket The UDP socket used for communication.
   * @param otherEndpoint The endpoint of the remote connection.
   * @param incomingMessages The queue to store incoming messages.
   *
   * @details Initializes the NetworkConnection object with the provided parameters.
   * If the owner is a SERVER, it generates a handshake value for security purposes.
   * For CLIENT, initializes handshake values to zero.
   */
  NetworkConnection(actualOwner owner, asio::io_context &otherAsioContext,
                    asio::ip::udp::socket socket,
                    asio::ip::udp::endpoint otherEndpoint,
                    rtype::network::ServerQueue<rtype::network::OwnedMessage<T>>
                        &incomingMessages)
      : asioSocket(std::move(socket)), endpoint(std::move(otherEndpoint)),
        asioContext(otherAsioContext),
        queueOfIncomingMessages(incomingMessages) {
    ownerType = owner;

    if (ownerType == actualOwner::SERVER) {
      handshakeOut =
          uint64_t(std::chrono::system_clock::now().time_since_epoch().count());
      handshakeCheck = scramble(handshakeOut);
    } else {
      handshakeOut = 0;
      handshakeIn = 0;
    }
  }

  /**
   * @brief Virtual destructor for the NetworkConnection class.
   *
   * This destructor ensures that derived class destructors are called properly
   * when an object of a derived class is deleted through a pointer to the base class.
   */
  virtual ~NetworkConnection() {}

  /**
   * @brief Retrieves the unique identifier of the network connection.
   *
   * @return uint32_t The unique identifier of the network connection.
   */
  uint32_t GetId() const { return id; }

  /**
   * @brief Retrieves the endpoint associated with the network connection.
   *
   * This function returns a constant reference to the UDP endpoint used by the network connection.
   *
   * @return const asio::ip::udp::endpoint& A constant reference to the UDP endpoint.
   */
  const asio::ip::udp::endpoint &GetEndpoint() const { return endpoint; }

  /**
   * @brief Get the UDP socket associated with the network connection.
   *
   * This function returns a constant reference to the ASIO UDP socket used by the network connection.
   *
   * @return const asio::ip::udp::socket& A constant reference to the ASIO UDP socket.
   */
  const asio::ip::udp::socket &GetSocket() const { return asioSocket; }

  /**
   * @brief Establishes a connection for a client to the server.
   *
   * This function is used to establish a connection for a client to the specified server.
   * It checks if the owner type is SERVER and if the socket is open. If the socket is open,
   * it sets the client ID and initiates reading the header. If the socket is not open, it
   * prints an error message.
   *
   * @tparam T The type of the server.
   * @param server A pointer to the server to which the client will connect.
   * @param clientId The ID of the client. Default is 0.
   */
  void EstablishClientConnection(rtype::network::IServer<T> *server,
                                 uint32_t clientId = 0) {
    if (ownerType == actualOwner::SERVER) {
      if (asioSocket.is_open()) {
        id = clientId;
        ReadHeader();
      } else {
        std::cout << "Error : Socket is not open" << std::endl;
      }
    }
  }

  /**
   * @brief Establishes a connection to the server.
   *
   * This function is used to establish a connection to the server when the owner type is a client.
   * It reads the header and sends a message indicating server acceptance.
   */
  void EstablishServerConnection() {
    if (ownerType == actualOwner::CLIENT) {
      ReadHeader();
      rtype::network::Message<NetworkMessages> message;
      message.header.id = NetworkMessages::ServerAcceptance;
      Send(message);
    }
  }

  /**
   * @brief Checks if the network connection is currently open.
   *
   * @return true if the socket is open and the connection is established, false otherwise.
   */
  bool IsConnected() const { return asioSocket.is_open(); }

  /**
   * @brief Disconnects the network connection if it is currently connected.
   *
   * This function checks if the network connection is active by calling the
   * IsConnected() method. If the connection is active, it posts a task to the
   * ASIO context to close the socket asynchronously.
   */
  void Disconnect() {
    if (IsConnected()) {
      asio::post(asioContext, [this]() { asioSocket.close(); });
    }
  }

  /**
   * @brief Sends a message through the network connection.
   *
   * This function posts a task to the ASIO context to send a message. If there are no other messages currently being sent,
   * it initiates the process by calling WriteHeader().
   *
   * @param message The message to be sent, encapsulated in a rtype::network::Message object.
   */
  void Send(const rtype::network::Message<T> &message) {
    asio::post(asioContext, [this, message]() {
      bool writingMessage = !queueOfOutgoingMessages.empty();
      queueOfOutgoingMessages.pushBack(message);
      if (!writingMessage) {
        WriteHeader();
      }
    });
  }

protected:
  /**
   * @brief A socket for sending and receiving datagrams using the UDP protocol.
   *
   * This socket is part of the ASIO library and is used for network communication
   * over the User Datagram Protocol (UDP). It provides asynchronous and synchronous
   * operations for sending and receiving data.
   *
   * @see https://think-async.com/Asio/asio-1.18.2/doc/asio/reference/ip__udp/socket.html
   */
  asio::ip::udp::socket asioSocket;

  /**
   * @brief Represents a network endpoint for UDP communication.
   *
   * This class encapsulates the endpoint information for a UDP connection,
   * including the IP address and port number. It is used to specify the
   * destination or source of a UDP datagram.
   */
  asio::ip::udp::endpoint endpoint;

  /**
   * @brief Reference to an ASIO io_context object.
   *
   * This member holds a reference to an ASIO io_context object, which is used to provide core I/O functionality
   * such as asynchronous operations, timers, and event handling. The io_context object is essential for managing
   * asynchronous I/O operations in a networked application.
   */
  asio::io_context &asioContext;

  actualOwner ownerType = actualOwner::SERVER;

  /**
   * @brief Reference to a queue that holds incoming messages.
   *
   * This member holds a reference to a ServerQueue that contains
   * OwnedMessage objects of type T. It is used to manage and process
   * incoming messages from the network.
   */
  rtype::network::ServerQueue<rtype::network::OwnedMessage<T>>
      &queueOfIncomingMessages;

  /**
   * @brief A queue that holds outgoing messages to be sent to the server.
   *
   * This queue is used to store messages of type `rtype::network::Message<T>`
   * that are intended to be sent to the server. It ensures that messages
   * are sent in the order they are queued.
   *
   * @tparam T The type of the message payload.
   */
  rtype::network::ServerQueue<rtype::network::Message<T>>
      queueOfOutgoingMessages;

  /**
   * @brief A temporary incoming message of type T.
   *
   * This variable is used to store a message that has been received over the network.
   * The type of the message is determined by the template parameter T.
   *
   * @tparam T The type of the message.
   */
  rtype::network::Message<T> temporaryIncomingMessage;

  /**
   * @brief Unique identifier for the network connection.
   */
  uint32_t id = 0;

  /**
   * @brief A variable used to store the outgoing handshake value.
   *
   * This variable is used in the network connection process to store
   * the value that will be sent as part of the handshake procedure.
   */
  uint64_t handshakeOut = 0;

  /**
   * @brief Stores the handshake input value.
   *
   * This variable is used to store the value received during the handshake process.
   * It is a 64-bit unsigned integer.
   */
  uint64_t handshakeIn = 0;

  /**
   * @brief Variable to store the handshake check value.
   *
   * This variable is used to verify the integrity and authenticity of the
   * handshake process in the network connection. It holds a 64-bit unsigned
   * integer value that represents the state or result of the handshake check.
   */
  uint64_t handshakeCheck = 0;

private:
  /**
   * @brief Asynchronously sends the header of the front message in the outgoing message queue.
   *
   * This function initiates an asynchronous send operation to transmit the header of the message
   * at the front of the outgoing message queue. If the header is successfully sent and the message
   * has a body, it proceeds to send the body by calling WriteBody(). If the message does not have
   * a body, it removes the message from the queue and, if there are more messages in the queue,
   * recursively calls itself to send the next message's header.
   *
   * In case of an error during the send operation, it logs the error and closes the socket.
   */
  void WriteHeader() {
    asioSocket.async_send_to(
        asio::buffer(&queueOfOutgoingMessages.front().header,
                     sizeof(rtype::network::MessageHeader<T>)),
        endpoint, [this](std::error_code ec, std::size_t bytesReceived) {
          if (!ec) {
            if (queueOfOutgoingMessages.front().body.size() > 0) {
              WriteBody();
            } else {
              queueOfOutgoingMessages.popFront();
              if (!queueOfOutgoingMessages.empty()) {
                std::cout << "Goes back on the same method" << std::endl;
                WriteHeader();
              }
            }
          } else {
            std::cout << id << " : Write Header failed" << ec << std::endl;
            asioSocket.close();
          }
        });
  }

  /**
   * @brief Asynchronously sends the body of the front message in the outgoing message queue.
   *
   * This function sends the body of the front message in the queueOfOutgoingMessages to the specified endpoint
   * using the asioSocket. Upon completion, it either pops the front message from the queue and calls WriteHeader()
   * if there are more messages to send, or handles any errors by closing the socket and printing an error message.
   *
   * @note This function is part of an asynchronous operation and should be called when there are messages in the queue.
   */
  void WriteBody() {
    asioSocket.async_send_to(
        asio::buffer(queueOfOutgoingMessages.front().body.data(),
                     queueOfOutgoingMessages.front().body.size()),
        endpoint, [this](std::error_code ec, std::size_t bytesReceived) {
          if (!ec) {
            queueOfOutgoingMessages.popFront();
            if (!queueOfOutgoingMessages.empty()) {
              WriteHeader();
            }
          } else {
            std::cout << id << " : Write Body failed" << ec << std::endl;
            asioSocket.close();
          }
        });
  }

  /**
   * @brief Adds a message to the incoming message queue.
   *
   * This function adds a message to the queue of incoming messages. If the owner
   * type is SERVER, it pushes the message along with a shared pointer to the
   * current instance. Otherwise, it pushes the message with a nullptr.
   * After adding the message to the queue, it initiates reading the next message header.
   */
  void AddMessageToIncomingQueue() {
    if (ownerType == actualOwner::SERVER)
      queueOfIncomingMessages.pushBack(
          {this->shared_from_this(), temporaryIncomingMessage});
    else
      queueOfIncomingMessages.pushBack({nullptr, temporaryIncomingMessage});
    ReadHeader();
  }

  /**
   * @brief Initiates an asynchronous read operation to read the header of an incoming message.
   *
   * This function uses the ASIO library to asynchronously receive data from the socket.
   * It reads the header of the incoming message and checks if there is any error during the operation.
   * If the header indicates that the message has a body, it resizes the body buffer and calls ReadBody() to read the body.
   * If the header indicates that the message has no body, it adds the message to the incoming queue.
   * If an error occurs, it logs the error and closes the socket.
   *
   * @note If the error code is 125, it indicates that the connection was closed.
   */
  void ReadHeader() {
    asioSocket.async_receive_from(
        asio::buffer(&temporaryIncomingMessage.header,
                     sizeof(rtype::network::MessageHeader<T>)),
        endpoint, [this](std::error_code ec, std::size_t bytesReceived) {
          if (ec.value() == 125) {
            std::cout << "Connection closed" << std::endl;
            return;
          }
          if (!ec) {
            if (temporaryIncomingMessage.header.size > 0) {
              temporaryIncomingMessage.body.resize(
                  temporaryIncomingMessage.header.size);
              ReadBody();
            } else {
              AddMessageToIncomingQueue();
            }
          } else {
            std::cout << id << " : Read Header failed" << ec << std::endl;
            asioSocket.close();
          }
        });
  }

  /**
   * @brief Asynchronously reads the body of an incoming message.
   *
   * This function initiates an asynchronous receive operation to read the body
   * of a message from the socket into the temporaryIncomingMessage buffer. Upon
   * completion, it either adds the message to the incoming queue if successful,
   * or logs an error and closes the socket if there was a failure.
   */
  void ReadBody() {
    asioSocket.async_receive_from(
        asio::buffer(temporaryIncomingMessage.body.data(),
                     temporaryIncomingMessage.body.size()),
        endpoint, [this](std::error_code ec, std::size_t bytesReceived) {
          if (!ec) {
            AddMessageToIncomingQueue();
          } else {
            std::cout << id << " : Read Body failed" << ec << std::endl;
            asioSocket.close();
          }
        });
  }

  //! Need to change the way I encrypt the message later
  /**
   * @brief Scrambles a 64-bit unsigned integer using bitwise operations.
   *
   * This function takes a 64-bit unsigned integer as input and performs a series
   * of bitwise operations to scramble its value. The scrambling process involves
   * XORing the input with a fixed value, shifting bits, and then XORing again
   * with another fixed value.
   *
   * @param n The 64-bit unsigned integer to be scrambled.
   * @return The scrambled 64-bit unsigned integer.
   */
  uint64_t scramble(uint64_t n) {
    uint64_t result = n ^ 0xDEADBEEFC0DECAFE;
    result =
        (result & 0xF0F0F0F0DEADBEEF) << 4 | (result & 0xF0F0F0F00000000) >> 4;
    return result ^ 0xC0DEFACE12345678;
  }

  /**
   * @brief Initiates the validation process by sending a handshake message.
   *
   * This function sends a handshake message asynchronously to the specified endpoint.
   * It uses the asio library for asynchronous operations. The function checks if the
   * handshake is successful and proceeds accordingly. If the handshake fails or an
   * error occurs during the send operation, the socket is closed.
   *
   * The function behaves differently based on the owner type:
   * - If the owner is a client, it checks if the received handshake matches the expected value.
   * - If the owner is a server, it scrambles the handshake and sends it back for validation.
   *
   * @note This function is part of the network connection handling and is used to ensure
   *       that the connection is valid and secure.
   */
  void WriteValidation() {
    asioSocket.async_send_to(
        asio::buffer(&handshakeOut, sizeof(uint64_t)), endpoint,
        [this](std::error_code ec, std::size_t bytesReceived) {
          if (!ec) {
            if (ownerType == actualOwner::CLIENT) {
              if (handshakeCheck == handshakeIn) {
                std::cout << "Handshake successful" << std::endl;
                ReadHeader();
              } else {
                std::cout << "Handshake failed" << std::endl;
                asioSocket.close();
              }
            } else {
              handshakeOut = scramble(handshakeIn);
              WriteValidation();
            }
          } else {
            std::cout << id << " : Write Validation failed" << ec << std::endl;
            asioSocket.close();
          }
        });
  }
};
} // namespace network
} // namespace rtype

#endif /* !NETWORKCONNECTION_HPP_ */