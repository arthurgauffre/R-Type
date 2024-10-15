/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#pragma once

#include <AClient.hpp>
#include <CoreModule.hpp>
#include <NetworkMessage.hpp>
#include <NetworkMessagesCommunication.hpp>

namespace rtype {
namespace network {
class Client : virtual public rtype::network::AClient<NetworkMessages> {
public:
  Client()
      : AClient(){}

  // void init() {
  //   component::ComponentManager &componentManager =
  //       *_coreModule->getComponentManager();
  //   entity::EntityManager &entityManager = *_coreModule->getEntityManager();

  //   _coreModule->getSystemManager()->addSystem(componentManager, entityManager,
  //                                              "render");
  //   _coreModule->getSystemManager()->addSystem(componentManager, entityManager,
  //                                              "audio");
  //   _coreModule->getSystemManager()->addSystem(componentManager, entityManager,
  //                                              "background");
  //   _coreModule->getSystemManager()->addSystem(componentManager, entityManager,
  //                                              "input");
  // }

  void PingServer() {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::ServerPing;
    PositionComponent pos = {1.0f, 5.0f};
    // Serialize PositionComponent into bytes
    std::vector<uint8_t> posBytes(reinterpret_cast<uint8_t *>(&pos),
                                  reinterpret_cast<uint8_t *>(&pos) +
                                      sizeof(PositionComponent));
    message.body.insert(message.body.end(), posBytes.begin(), posBytes.end());
    std::chrono::system_clock::time_point timeNow =
        std::chrono::system_clock::now();

    message << timeNow;

    Send(message);
    std::cout << "Message sent : " << message << std::endl;
  }

  void CreateEntity()
  {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::createEntity;
    // Serialize the entityID into bytes
    EntityId id = {1};
    std::cout << id.id << std::endl;
    // std::vector<uint8_t> entityIDBytes(reinterpret_cast<uint8_t *>(&id), reinterpret_cast<uint8_t *>(&id) + sizeof(EntityId));
    std::vector<uint8_t> entityIDBytes(reinterpret_cast<uint8_t *>(&id), reinterpret_cast<uint8_t *>(&id) + sizeof(EntityId));
    std::cout << entityIDBytes.size() << std::endl;

    message.body.insert(message.body.end(), entityIDBytes.begin(), entityIDBytes.end());
    Send(message);
    std::cout << "Message sent : " << message << std::endl;
  }

  void SendMessageToAllClients() {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::MessageAll;

    Send(message);
  }

  void run() {
    std::vector<std::string> msgToSend;
    sf::Clock clock;
    while (1) {
      float deltaTime = clock.restart().asSeconds();
      _coreModule.get()->getSystemManager()->update(
          deltaTime, _coreModule.get()->getEntityManager()->getEntities(),
          msgToSend);
    }
    std::cout << "Client running" << std::endl;
  };

  virtual void Disconnect() {}

private:
  std::shared_ptr<CoreModule> _coreModule;
  size_t entityID = 0;
};
} // namespace network
} // namespace rtype

#endif /* !CLIENT_HPP_ */
