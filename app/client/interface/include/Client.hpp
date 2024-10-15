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
#include <NetworkMessage.hpp>
#include <NetworkMessagesCommunication.hpp>

namespace rtype {
namespace network {
class Client : virtual public rtype::network::AClient<NetworkMessages> {
public:
  void PingServer() {
    rtype::network::Message<NetworkMessages> message;
    message.header.id = NetworkMessages::ServerPing;
    PositionComponent pos = {1.0f, 5.0f};
    // Serialize PositionComponent into bytes
    std::vector<uint8_t> posBytes(reinterpret_cast<uint8_t*>(&pos), reinterpret_cast<uint8_t*>(&pos) + sizeof(PositionComponent));
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

  virtual void Disconnect() {}
};
} // namespace network
} // namespace rtype

#endif /* !CLIENT_HPP_ */
