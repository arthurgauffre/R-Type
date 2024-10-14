/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** IClient
*/

#ifndef ICLIENT_HPP_
#define ICLIENT_HPP_

#pragma once

#include <NetworkConnection.hpp>
#include <NetworkQueue.hpp>
#include <NetworkingCommon.hpp>

namespace rtype {
namespace network {
template <typename T> class IClient {
public:
  IClient() {}
  virtual ~IClient() {}

  virtual bool Connect(const std::string &host, const uint16_t port) = 0;
  virtual void Disconnect() = 0;
  virtual bool IsConnected() = 0;

  virtual void Send(const rtype::network::Message<T> &message) = 0;
  virtual rtype::network::ServerQueue<rtype::network::OwnedMessage<T>> &
  GetIncomingMessages() = 0;
};
} // namespace network
} // namespace rtype

#endif /* !ICLIENT_HPP_ */
