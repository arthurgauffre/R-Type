/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#pragma once

#include <NetworkMessage.hpp>
#include <NetworkMessagesCommunication.hpp>
#include <AClient.hpp>

namespace rtype{
  namespace network {
    class Client : virtual public rtype::network::AClient<NetworkMessages>
    {
    public:
      void PingServer()
      {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::ServerPing;
        // std::chrono::system_clock::time_point timeNow =
        //     std::chrono::system_clock::now();

        // message << timeNow;

        // Send(message);
      }

      void SendMessageToAllClients()
      {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::MessageAll;

        // Send(message);
      }

      virtual void Disconnect() {}
    };
  } // namespace network
} // namespace rtype

#endif /* !CLIENT_HPP_ */
