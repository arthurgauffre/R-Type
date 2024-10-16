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
#include <NetworkMessageFactory.hpp>
#include <NetworkMessagesCommunication.hpp>

namespace rtype {
namespace network {
class Client : virtual public rtype::network::AClient<NetworkMessages> {
public:
  Client() : AClient() {
    _coreModule = std::make_shared<CoreModule>();
    init();
  }

  void init() {
    component::ComponentManager &componentManager =
        *_coreModule->getComponentManager();
    entity::EntityManager &entityManager = *_coreModule->getEntityManager();

    _coreModule->getSystemManager()->addSystem(componentManager, entityManager,
                                               "render");
    _coreModule->getSystemManager()->addSystem(componentManager, entityManager,
                                               "audio");
    _coreModule->getSystemManager()->addSystem(componentManager, entityManager,
                                               "background");
    _coreModule->getSystemManager()->addSystem(componentManager, entityManager,
                                               "input");
  }

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

  void SendMessageToAllClients() {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::MessageAll;

    Send(message);
  }

  void handdleMessage(rtype::network::Message<NetworkMessages> &msg);

  void run();

  std::string GetTexturePath(TexturePath texture);

      KeyAction getAction(std::string action);

      virtual void Disconnect() {}

private:
  std::shared_ptr<CoreModule> _coreModule;
  uint8_t entityID = 0;
  NetworkMessageFactory _networkMessageFactory;
};
} // namespace network
} // namespace rtype

#endif /* !CLIENT_HPP_ */
