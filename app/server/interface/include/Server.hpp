/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#pragma once

#include <AServer.hpp>
#include <CoreModule.hpp>
#include <NetworkMessagesCommunication.hpp>

namespace rtype {
namespace network {
class Server : virtual public rtype::network::AServer<NetworkMessages> {
public:
  Server(uint16_t port)
      : rtype::network::IServer<NetworkMessages>(),
        rtype::network::AServer<NetworkMessages>(port) {}

  ~Server(){};

  virtual void run() {
    std::vector<std::string> msgToSend;
    sf::Clock clock;
    while (1) {
      float deltatime = clock.restart().asSeconds();
      this->Update(deltatime, false);
      std::lock_guard<std::mutex> lock(coreModuleMutex);
      _coreModule.get()->getSystemManager()->update(
          deltatime, _coreModule.get()->getEntityManager()->getEntities(),
          msgToSend);
    }
  }

protected:
  virtual void OnMessageReceived(
      std::shared_ptr<rtype::network::NetworkConnection<NetworkMessages>>
          client,
      rtype::network::Message<NetworkMessages> &message) {
    std::cout << "Message received from client : " << client->GetId()
              << std::endl;
    switch (message.header.id) {
    case NetworkMessages::ClientConnection: {
      std::cout << "Client connected : " << client->GetId() << std::endl;
    } break;
    case NetworkMessages::MessageAll: {
      rtype::network::Message<NetworkMessages> message;
      message.header.id = NetworkMessages::ServerMessage;
      message << client->GetId();
      SendMessageToAllClients(message, client);
    } break;
    case NetworkMessages::ServerPing: {
      std::cout << client->GetId() << " : Ping the server" << std::endl;
      client->Send(message);
    } break;
    case NetworkMessages::createEntity: {
      std::cout << "creation of the entity" << std::endl;
    } break;
    }
  }

  virtual bool OnClientConnection(
      std::shared_ptr<rtype::network::NetworkConnection<NetworkMessages>>
          client) {
    std::cout << "Client is attempting to connect" << std::endl;
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::ServerAcceptance;
    client->Send(message);

    return true;
  }

  virtual void OnClientDisconnection(
      std::shared_ptr<rtype::network::NetworkConnection<NetworkMessages>>
          client) {
    // std::cout << "Client disconnected : " << client->GetId() << std::endl;
  }

private:
};
} // namespace network
} // namespace rtype

#endif /* !SERVER_HPP_ */
