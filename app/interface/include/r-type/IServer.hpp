/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** IServer
*/

#ifndef ISERVER_HPP_
#define ISERVER_HPP_

#pragma once

#include <NetworkConnection.hpp>
#include <NetworkMessage.hpp>
#include <NetworkingCommon.hpp>

namespace rtype {
namespace network {
template <typename T> class IServer {
public:
  IServer(){};
  virtual ~IServer(){};

  virtual bool Start() = 0;
  virtual void Stop() = 0;

            virtual void WaitForMessage() = 0;

            virtual void SendMessageToClient(const rtype::network::Message<T> &message, std::shared_ptr<rtype::network::NetworkConnection<T>> client) = 0;
            virtual void SendMessageToAllClients(const rtype::network::Message<T> &message, std::shared_ptr<rtype::network::NetworkConnection<T>> clientToIgnore = nullptr) = 0;
            virtual void Update(size_t maxMessages = -1, bool needToWait = false) = 0;
            virtual void OnClientValidated(std::shared_ptr<rtype::network::NetworkConnection<T>> client) = 0;

        protected:
            virtual void OnMessageReceived(std::shared_ptr<NetworkConnection<T>> client, rtype::network::Message<T> &message) = 0;
            virtual bool OnClientConnection(std::shared_ptr<rtype::network::NetworkConnection<T>> client) = 0;
            virtual void OnClientDisconnection(std::shared_ptr<rtype::network::NetworkConnection<T>> client) = 0;

        };
    }
}

#endif /* !ISERVER_HPP_ */
