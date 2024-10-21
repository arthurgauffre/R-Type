/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#pragma once

#include <r-type/IServer.hpp>
#include <CoreModule.hpp>
#include <NetworkMessagesCommunication.hpp>
#include <NetworkMessageFactory.hpp>
#include <NetworkConnection.hpp>
#include <NetworkQueue.hpp>
#include <NetworkMessage.hpp>
#include <Error.hpp>
#include <r-type/ASystem.hpp>

namespace rtype {
namespace network {
template <typename T>
class ServerSystem : virtual public rtype::network::IServer<NetworkMessages>,
                     virtual public ECS_system::ASystem {
public:
  ServerSystem(component::ComponentManager &componentManager,
               entity::EntityManager &entityManager)
      : rtype::network::IServer<NetworkMessages>(), ECS_system::ASystem(
                                                        componentManager,
                                                        entityManager), _componentManager(componentManager), _entityManager(entityManager), asioSocket(asioContext,
                   asio::ip::udp::endpoint(asio::ip::udp::v4(), 60000)) {
    Start();
  }

  ~ServerSystem(){ Stop(); };

  void initialize(){};

  void handleComponents(){};

  std::vector<std::string>
  update(float deltaTime,
         std::vector<std::shared_ptr<entity::IEntity>> entities,
         std::vector<std::string> msgToSend) {
    sf::Clock clock;
    float deltatime = clock.restart().asSeconds();
    this->ServerUpdate(deltatime, false);
    return msgToSend;
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

  void WaitForMessage() {
    asioSocket.async_receive_from(
        asio::buffer(bufferOfIncomingMessages.data(),
                     bufferOfIncomingMessages.size()),
        clientEndpoint, [this](std::error_code ec, std::size_t bytesReceived) {
          if (clientEndpoint.protocol() != asio::ip::udp::v4())
            return WaitForMessage();;
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
              deqConnections.push_back(std::move(newConnection));
              deqConnections.back()->EstablishClientConnection(this,
                                                               actualId++);
              std::cout << "[" << deqConnections.back()->GetId()
                        << "] Connection approved" << std::endl;
              sendAllEntitiesToClient(deqConnections.back());
              size_t id =
                  _entityManager.generateEntityID();
              _entityManager.createEntity(id);
              SendMessageToAllClients(
                  networkMessageFactory.createEntityMsg(id));
              _componentManager.addComponent<component::PositionComponent>(id, 0, 0);
              SendMessageToAllClients(
                  networkMessageFactory.createPositionMsg(id, 0, 0));
              _componentManager.addComponent<component::SpriteComponent>(id, 0, 0);
              SendMessageToAllClients(
                  networkMessageFactory.createSpriteMsg(id, 0, 0));
              _componentManager.addComponent<component::TextureComponent>(
                      id, GetTexturePath(TexturePath::Player));
              SendMessageToAllClients(networkMessageFactory.createTextureMsg(
                  id, TexturePath::Player));
              _componentManager.addComponent<component::TransformComponent>(
                      id, sf::Vector2f(0, 0), sf::Vector2f(1, 1));
              SendMessageToAllClients(
                  networkMessageFactory.createTransformMsg(id, 0, 0, 1, 1));
            } else {
              std::cout << "Connection denied" << std::endl;
            }
          } else {
            std::cout << "Error on connection" << ec.message() << std::endl;
          }
          WaitForMessage();
        });
  }

  void sendAllEntitiesToClient(std::shared_ptr<NetworkConnection<T>> client)
  {
    if (client->IsConnected() == false)
    {
      std::cout << "Client is not connected" << std::endl;
    }
    else
    {
      std::cout << "Client is connected" << std::endl;
    }
    _entityManager.getEntities();
    for (auto &entity : _entityManager.getEntities())
    {
      SendMessageToClient(
          networkMessageFactory.createEntityMsg(entity->getID()), client);
      if (_componentManager.getComponent<component::PositionComponent>(entity->getID()))
      {
        component::PositionComponent *component =
            _componentManager.getComponent<component::PositionComponent>(entity->getID());
        SendMessageToClient(
            networkMessageFactory.createPositionMsg(
                entity->getID(), component->getX(), component->getY()),
            client);
      }
      if (_componentManager.getComponent<component::SpriteComponent>(entity->getID()))
      {
        component::SpriteComponent *component =
            _componentManager.getComponent<component::SpriteComponent>(entity->getID());
        SendMessageToClient(
            networkMessageFactory.createSpriteMsg(
                entity->getID(), component->getX(), component->getY()),
            client);
      }
      if (_componentManager.getComponent<component::TextureComponent>(entity->getID()))
      {
        component::TextureComponent *component =
            _componentManager.getComponent<component::TextureComponent>(entity->getID());
        SendMessageToClient(
            networkMessageFactory.createTextureMsg(
                entity->getID(), GetEnumTexturePath(component->getPath())),
            client);
      }
      if (_componentManager.getComponent<component::TransformComponent>(entity->getID()))
      {
        component::TransformComponent *component =
            _componentManager.getComponent<component::TransformComponent>(entity->getID());
        SendMessageToClient(networkMessageFactory.createTransformMsg(
                                entity->getID(), component->getPosition().x,
                                component->getPosition().y,
                                component->getScale().x,
                                component->getScale().y),
                            client);
      }
      if (_componentManager.getComponent<component::BackgroundComponent>(entity->getID()))
      {
        component::BackgroundComponent *component =
            _componentManager.getComponent<component::BackgroundComponent>(entity->getID());
        SendMessageToClient(networkMessageFactory.createBackgroundMsg(
                                entity->getID(),
                                GetEnumTexturePath(component->getTexturePath()),
                                component->getSize().x, component->getSize().y),
                            client);
      }
      if (_componentManager.getComponent<component::ScrollComponent>(entity->getID()))
      {
        component::ScrollComponent *component =
            _componentManager.getComponent<component::ScrollComponent>(entity->getID());
        SendMessageToClient(networkMessageFactory.createScrollMsg(
                                entity->getID(), component->getScrollSpeed().x,
                                component->getScrollSpeed().y),
                            client);
      }
      if (_componentManager.getComponent<component::HealthComponent>(entity->getID()))
      {
        component::HealthComponent *component =
            _componentManager.getComponent<component::HealthComponent>(entity->getID());
        SendMessageToClient(networkMessageFactory.createHealthMsg(
                                entity->getID(), component->getHealth()),
                            client);
      }
      if (_componentManager.getComponent<component::DamageComponent>(entity->getID()))
      {
        component::DamageComponent *component =
            _componentManager.getComponent<component::DamageComponent>(entity->getID());
        SendMessageToClient(networkMessageFactory.createDamageMsg(
                                entity->getID(), component->getDamage()),
                            client);
      }
      if (_componentManager.getComponent<component::HitBoxComponent>(entity->getID()))
      {
        component::HitBoxComponent *component =
            _componentManager.getComponent<component::HitBoxComponent>(entity->getID());
        SendMessageToClient(
            networkMessageFactory.createHitboxMsg(
                entity->getID(), component->getHeight(), component->getWidth()),
            client);
      }
      // if
      // (_coreModule.get()->getComponentManager()->getComponent<component::MusicComponent>(entity->getID()))
      //   SendMessageToClient(networkMessageFactory.createMusicMsg(entity->getID(),
      //   dynamic_cast<component::MusicComponent
      //   *>(component.get())->musicPath), client);
      // if
      // (_coreModule.get()->getComponentManager()->getComponent<component::SoundComponent>(entity->getID()))
      //   SendMessageToClient(networkMessageFactory.createSoundMsg(entity->getID(),
      //   dynamic_cast<component::SoundComponent
      //   *>(component.get())->soundPath), client);
      if (_componentManager.getComponent<component::ParentComponent>(entity->getID()))
      {
        component::ParentComponent *component =
            _componentManager.getComponent<component::ParentComponent>(entity->getID());
        SendMessageToClient(networkMessageFactory.createParentMsg(
                                entity->getID(), component->getParentID()),
                            client);
      }
    }
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

private:
  component::ComponentManager &_componentManager;
  entity::EntityManager &_entityManager;
};
} // namespace network
} // namespace rtype

#endif /* !SERVER_HPP_ */
