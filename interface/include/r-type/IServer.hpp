/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** IServer
*/

#ifndef ISERVER_HPP_
#define ISERVER_HPP_

#pragma once

#include <RtypeEngine.hpp>
#include <NetworkConnection.hpp>
#include <NetworkMessage.hpp>
#include <NetworkingCommon.hpp>

namespace rtype {
namespace network {
template <typename T> class IServer {
public:
/**
 * @brief Construct a new IServer object.
 */
  IServer(){};

/**
 * @brief Virtual destructor for the IServer interface.
 *
 * This destructor ensures that derived classes can clean up resources properly
 * when an object of a derived class is deleted through a pointer to IServer.
 */
  virtual ~IServer(){};

/**
 * @brief Starts the server.
 *
 * This function initializes and starts the server, making it ready to accept connections and handle requests.
 *
 * @return true if the server started successfully, false otherwise.
 */
  virtual bool Start() = 0;

/**
 * @brief Stops the server.
 *
 * This function is responsible for stopping the server and performing any necessary cleanup operations.
 * It should be called when the server needs to be shut down gracefully.
 */
  virtual void Stop() = 0;

/**
 * @brief Waits for a message from the client.
 *
 * This pure virtual function should be implemented by derived classes to
 * handle the logic for waiting and processing incoming messages from clients.
 */
  virtual void WaitForMessage() = 0;

/**
 * @brief Sends a message to a specific client.
 *
 * @param message The message to be sent to the client.
 * @param client A shared pointer to the client's network connection.
 */
  virtual void SendMessageToClient(
      const rtype::network::Message<T> &message,
      std::shared_ptr<rtype::network::NetworkConnection<T>> client) = 0;

/**
 * @brief Sends a message to all connected clients.
 *
 * This function sends the specified message to all clients connected to the server.
 * Optionally, a specific client can be ignored and not receive the message.
 *
 * @param message The message to be sent to all clients.
 * @param clientToIgnore A shared pointer to the client that should be ignored.
 *                       If nullptr, the message will be sent to all clients.
 */
  virtual void SendMessageToAllClients(
      const rtype::network::Message<T> &message,
      std::shared_ptr<rtype::network::NetworkConnection<T>> clientToIgnore =
          nullptr) = 0;

/**
 * @brief Updates the server state.
 *
 * @param maxMessages The maximum number of messages to process in this update cycle.
 *                    Defaults to -1, which indicates no limit.
 * @param needToWait  If true, the function will wait for new messages if none are available.
 *                    Defaults to false.
 */
  virtual void ServerUpdate(size_t maxMessages = -1,
                            bool needToWait = false) = 0;

/**
 * @brief This method is called when a client has been successfully validated.
 *
 * @param client A shared pointer to the validated network connection of the client.
 */
  virtual void OnClientValidated(
      std::shared_ptr<rtype::network::NetworkConnection<T>> client) = 0;

protected:
/**
 * @brief This method is called when a message is received from a client.
 *
 * @param client A shared pointer to the network connection of the client that sent the message.
 * @param message A reference to the message received from the client.
 */
  virtual void OnMessageReceived(std::shared_ptr<NetworkConnection<T>> client,
                                 rtype::network::Message<T> &message) = 0;

/**
 * @brief Handles the event of a new client connection.
 *
 * This method is called when a new client establishes a connection with the server.
 * Implement this method to define custom behavior for handling new client connections.
 *
 * @param client A shared pointer to the NetworkConnection object representing the client.
 * @return true if the client connection is accepted, false otherwise.
 */
  virtual bool OnClientConnection(
      std::shared_ptr<rtype::network::NetworkConnection<T>> client) = 0;

/**
 * @brief This method is called when a client disconnects from the server.
 *
 * @param client A shared pointer to the NetworkConnection object representing the client that has disconnected.
 */
  virtual void OnClientDisconnection(
      std::shared_ptr<rtype::network::NetworkConnection<T>> client) = 0;
};
} // namespace network
} // namespace rtype

#endif /* !ISERVER_HPP_ */
