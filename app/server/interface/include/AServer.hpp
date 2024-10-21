/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AServer
*/

#ifndef ASERVER_HPP_
#define ASERVER_HPP_

#pragma once

#include <Error.hpp>
#include <r-type/IServer.hpp>
// #include <NetworkingCommon.hpp>
#include <NetworkMessageFactory.hpp>
#include <NetworkQueue.hpp>
#include <OwnedMessage.hpp>
#include <mutex>

namespace rtype {
namespace network {
template <typename T> class AServer : virtual public IServer<T> {
public:
  std::mutex coreModuleMutex;
  AServer()
      : rtype::network::IServer<T>(),
        asioSocket(asioContext,
                   asio::ip::udp::endpoint(asio::ip::udp::v4(), 60000)) {
    // _coreModule = std::make_shared<CoreModule>();
    // init();
    // clientEndpoint(asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
  }

  ~AServer() { Stop(); }

  virtual void init() {
    // component::ComponentManager &componentManager =
    //     *_coreModule->getComponentManager();
    // entity::EntityManager &entityManager = *_coreModule->getEntityManager();

    // _coreModule->getSystemManager()->addSystem(componentManager,
    // entityManager,
    //  "collision");
    // _coreModule->getSystemManager()->addSystem(componentManager,
    // entityManager,
    //                                            "movement");
    // _coreModule->getSystemManager()->addSystem(componentManager,
    // entityManager,
    //                                            "health");

    // uint32_t backgroundEntityID =
    //     _coreModule->getEntityManager()->generateEntityID();
    // _coreModule->getEntityManager()->createEntity(backgroundEntityID);
    // _coreModule->getComponentManager()
    //     ->addComponent<component::PositionComponent>(backgroundEntityID,
    //     0.0f,
    //                                                  0.0f);
    // _coreModule->getComponentManager()
    //     ->addComponent<component::ScrollComponent>(backgroundEntityID,
    //                                                sf::Vector2f(100.0f,
    //                                                0.0f));
    // _coreModule->getComponentManager()
    //     ->addComponent<component::BackgroundComponent>(
    //         backgroundEntityID, GetTexturePath(TexturePath::Background),
    //         sf::Vector2f(1920.0f, 1080.0f));
  }

  bool Start() {
    try {
      WaitForMessage();

      contextThread = std::thread([this]() { asioContext.run(); });
    } catch (rtype::RtypeException &e) {
      std::cerr << "Server exception :" << e.what() << std::endl;
      return false;
    }
    std::cout << "Server started !" << std::endl;
    return true;
  }

  void Stop() {
    asioContext.stop();

    if (contextThread.joinable())
      contextThread.join();
    std::cout << "Server stopped !" << std::endl;
  }

  void WaitForMessage() {
    asioSocket.async_receive_from(
        asio::buffer(bufferOfIncomingMessages.data(),
                     bufferOfIncomingMessages.size()),
        clientEndpoint, [this](std::error_code ec, std::size_t bytesReceived) {
          if (clientEndpoint.protocol() != asio::ip::udp::v4())
            return WaitForMessage();
          if (!ec) {
            std::cout << "New connection from: " << clientEndpoint << std::endl;

            for (std::shared_ptr<NetworkConnection<T>> &connection :
                 deqConnections) {
              if (connection->GetEndpoint() == clientEndpoint) {
                std::cout << "Connection already exists" << std::endl;
                return;
              }
            }

            asio::ip::udp::socket newSocket(
                asioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0));

            std::shared_ptr<NetworkConnection<T>> newConnection =
                std::make_shared<NetworkConnection<T>>(
                    NetworkConnection<T>::actualOwner::SERVER, asioContext,
                    std::move(newSocket), clientEndpoint, incomingMessages);
            if (OnClientConnection(newConnection)) {
              std::lock_guard<std::mutex> lock(coreModuleMutex);
              deqConnections.push_back(std::move(newConnection));
              deqConnections.back()->EstablishClientConnection(this,
                                                               actualId++);
              std::cout << "[" << deqConnections.back()->GetId()
                        << "] Connection approved" << std::endl;
              // add to a function
              // sendAllEntitiesToClient(deqConnections.back());
              // size_t id =
              //     _coreModule.get()->getEntityManager()->generateEntityID();
              // _coreModule.get()->getEntityManager()->createEntity(id);
              // SendMessageToAllClients(
              //     networkMessageFactory.createEntityMsg(id));
              // _coreModule.get()
              //     ->getComponentManager()
              //     ->addComponent<component::PositionComponent>(id, 0, 0);
              // SendMessageToAllClients(
              //     networkMessageFactory.createPositionMsg(id, 0, 0));
              // _coreModule.get()
              //     ->getComponentManager()
              //     ->addComponent<component::SpriteComponent>(id, 0, 0);
              // SendMessageToAllClients(
              //     networkMessageFactory.createSpriteMsg(id, 0, 0));
              // _coreModule.get()
              //     ->getComponentManager()
              //     ->addComponent<component::TextureComponent>(
              //         id, GetTexturePath(TexturePath::Player));
              // SendMessageToAllClients(networkMessageFactory.createTextureMsg(
              //     id, TexturePath::Player));
              // _coreModule.get()
              //     ->getComponentManager()
              //     ->addComponent<component::TransformComponent>(
              //         id, sf::Vector2f(0, 0), sf::Vector2f(1, 1));
              // SendMessageToAllClients(
              //     networkMessageFactory.createTransformMsg(id, 0, 0, 1, 1));
            } else {
              std::cout << "Connection denied" << std::endl;
            }
          } else {
            std::cout << "Error on connection" << ec.message() << std::endl;
          }
          WaitForMessage();
        });
  }

  void SendMessageToClient(const Message<T> &message,
                           std::shared_ptr<NetworkConnection<T>> client) {
    std::cout << "checking message to client" << std::endl;
    if (client && client->IsConnected()) {
      std::cout << "Sending message to client" << std::endl;
      client->Send(message);
    } else {
      OnClientDisconnection(client);
      client.reset();
      deqConnections.erase(
          std::remove(deqConnections.begin(), deqConnections.end(), client),
          deqConnections.end());
    }
    std::cout << "Message sent to client" << std::endl;
  }

  void SendMessageToAllClients(
      const rtype::network::Message<T> &message,
      std::shared_ptr<rtype::network::NetworkConnection<T>> clientToIgnore =
          nullptr) {
    bool invalidClientExists = false;

    for (auto &client : deqConnections) {
      if (client && client->IsConnected()) {
        if (client != clientToIgnore)
          client->Send(message);
      } else {
        OnClientDisconnection(client);
        client.reset();
        invalidClientExists = true;
      }
    }
    if (invalidClientExists) {
      deqConnections.erase(
          std::remove(deqConnections.begin(), deqConnections.end(), nullptr),
          deqConnections.end());
    }
  }

  void ServerUpdate(size_t maxMessages = -1, bool needToWait = false) {
    if (needToWait == true)
      incomingMessages.wait();
    size_t messageCount = 0;
    while (messageCount < maxMessages && !incomingMessages.empty()) {
      auto message = incomingMessages.popFront();
      OnMessageReceived(message.remoteConnection, message.message);
      messageCount++;
    }
  }

  virtual void OnClientValidated(std::shared_ptr<NetworkConnection<T>> client) {
  }

  std::string GetTexturePath(TexturePath texture) {
    switch (texture) {
    case TexturePath::Background: {
      return "app/assets/images/city_background.png";
    } break;
    case TexturePath::Player: {
      return "app/assets/sprites/plane.png";
    } break;
      // case TexturePath::Enemy:
      // return "assets/enemy.png";
    }
    return "";
  }

  TexturePath GetEnumTexturePath(std::string texture) {
    if (texture == "app/assets/sprites/plane.png")
      return TexturePath::Player;
    // if (texture == "assets/enemy.png")
    //   return TexturePath::Enemy;
    if (texture == "app/assets/images/city_background.png")
      return TexturePath::Background;
    return TexturePath::Player;
  }

  rtype::network::ServerQueue<rtype::network::OwnedMessage<T>> incomingMessages;
  std::deque<std::shared_ptr<NetworkConnection<T>>> deqConnections;

  asio::io_context asioContext;
  std::thread contextThread;

  asio::ip::udp::socket asioSocket;
  asio::ip::udp::endpoint clientEndpoint;

  NetworkMessageFactory networkMessageFactory;
  std::array<char, 1024> bufferOfIncomingMessages;
  uint32_t actualId = 0;

protected:
  virtual void OnMessageReceived(std::shared_ptr<NetworkConnection<T>> client,
                                 Message<T> &message) {}
  virtual bool OnClientConnection(
      std::shared_ptr<rtype::network::NetworkConnection<T>> client) {
    return false;
  }
  virtual void OnClientDisconnection(
      std::shared_ptr<rtype::network::NetworkConnection<T>> client) {}
  // std::shared_ptr<CoreModule> _coreModule;
};
} // namespace network
} // namespace rtype

#endif /* !ASERVER_HPP_ */
