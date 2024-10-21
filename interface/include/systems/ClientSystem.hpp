/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ClientSystem
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#pragma once

#include <r-type/AClient.hpp>
#include <CoreModule.hpp>
#include <NetworkMessage.hpp>
#include <NetworkMessageFactory.hpp>
#include <NetworkMessagesCommunication.hpp>
#include <r-type/ASystem.hpp>

namespace rtype {
namespace network {
class ClientSystem : virtual public rtype::network::AClient<NetworkMessages>, virtual public ECS_system::ASystem {
public:
  ClientSystem(component::ComponentManager &componentManager,
                   entity::EntityManager &entityManager) : AClient(), ASystem(componentManager, entityManager), _componentManager(componentManager), _entityManager(entityManager) {
      Connect("127.0.0.1", 60000);
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

  std::string GetTexturePath(TexturePath texture);

  KeyAction getAction(std::string action);

  virtual void Disconnect() {}

  void initialize() override{};
  void handleComponents() override{};

  std::vector<std::string>
  update(float deltaTime,
         std::vector<std::shared_ptr<entity::IEntity>> entities,
         std::vector<std::string> msgToSend) override;

private:
  uint8_t entityID = 0;
  NetworkMessageFactory _networkMessageFactory;
  component::ComponentManager &_componentManager;
  entity::EntityManager &_entityManager;
};
} // namespace network
} // namespace rtype

#endif /* !CLIENT_HPP_ */
