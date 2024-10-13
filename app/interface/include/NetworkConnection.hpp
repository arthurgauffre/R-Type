/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** NetworkConnection
*/

#ifndef NETWORKCONNECTION_HPP_
#define NETWORKCONNECTION_HPP_

#pragma once

#include <NetworkQueue.hpp>
#include <OwnedMessage.hpp>
#include <r-type/IServer.hpp>

namespace rtype {
namespace network {
template <typename T> class IServer;
template <typename T>
class NetworkConnection
    : public std::enable_shared_from_this<NetworkConnection<T>> {
public:
  enum class actualOwner { SERVER, CLIENT };

  NetworkConnection(actualOwner owner, asio::io_context &otherAsioContext,
                    asio::ip::udp::socket socket,
                    asio::ip::udp::endpoint otherEndpoint,
                    rtype::network::ServerQueue<rtype::network::OwnedMessage<T>>
                        &incomingMessages)
      : asioSocket(std::move(socket)), endpoint(std::move(otherEndpoint)),
        asioContext(otherAsioContext),
        queueOfIncomingMessages(incomingMessages) {
    ownerType = owner;

    if (ownerType == actualOwner::SERVER) {
      // get the output of the handshake
      // assign the handsake check to the cryption method of the output
    } else {
      // set the handshale output and input to 0
    }
  }

  virtual ~NetworkConnection() {}

  uint32_t GetId() const { return id; }
  const asio::ip::udp::endpoint &GetEndpoint() const { return endpoint; }
  const asio::ip::udp::socket &GetSocket() const { return asioSocket; }

  void EstablishClientConnection(rtype::network::IServer<T> *server,
                                 uint32_t clientId = 0) {
    if (ownerType == actualOwner::SERVER) {
      if (asioSocket.is_open()) {
        id = clientId;
        ReadHeader();
      } else {
        std::cout << "Error : Socket is not open" << std::endl;
      }
    }
  }

  // void EstablishServerConnection()
  // {
  // }

  bool IsConnected() const { return asioSocket.is_open(); }
  void Disconnect() {
    if (IsConnected()) {
      asio::post(asioContext, [this]() { asioSocket.close(); });
    }
  }

  void Send(const rtype::network::Message<T> &message) {
    asio::post(asioContext, [this, message]() {
      bool writingMessage = !queueOfIncomingMessages.empty();
      queueOfIncomingMessages.pushBack(message);
      if (!writingMessage) {
        WriteHeader();
      }
    });
  }

protected:
  asio::ip::udp::socket asioSocket;
  asio::ip::udp::endpoint endpoint;
  asio::io_context &asioContext;
  actualOwner ownerType = actualOwner::SERVER;
  rtype::network::ServerQueue<rtype::network::OwnedMessage<T>>
      &queueOfIncomingMessages;
  rtype::network::Message<T> temporaryIncomingMessage;

  uint32_t id = 0;
  uint64_t handshakeOut = 0;
  uint64_t handshakeIn = 0;
  uint64_t handshakeCheck = 0;

private:
  void WriteHeader() {
    std::cout << "Sending to endpoint : " << endpoint << std::endl;
    asioSocket.async_send_to(
        asio::buffer(&queueOfIncomingMessages.front().header,
                     sizeof(rtype::network::MessageHeader<T>)),
        endpoint, [this](std::error_code ec, std::size_t bytesReceived) {
          if (!ec) {
            if (queueOfIncomingMessages.front().body.size() > 0) {
              WriteBody();
            } else {
              queueOfIncomingMessages.popFront();
              if (!queueOfIncomingMessages.empty()) {
                WriteHeader();
              }
            }
          } else {
            std::cout << id << " : Write Header failed" << ec << std::endl;
            asioSocket.close();
          }
        });
  }

  void WriteBody() {
    std::cout << "Sending to endpoint : " << endpoint << std::endl;

    asioSocket.async_send_to(
        asio::buffer(queueOfIncomingMessages.front().body.data(),
                     queueOfIncomingMessages.front().body.size()),
        endpoint, [this](std::error_code ec, std::size_t bytesReceived) {
          if (!ec) {
            queueOfIncomingMessages.popFront();
            if (!queueOfIncomingMessages.empty()) {
              WriteHeader();
            }
          } else {
            std::cout << id << " : Write Body failed" << ec << std::endl;
            asioSocket.close();
          }
        });
  }

  void AddMessageToIncomingQueue() {
    if (ownerType == actualOwner::SERVER)
      queueOfIncomingMessages.pushBack(
          {this->shared_from_this(), temporaryIncomingMessage});
    else
      queueOfIncomingMessages.pushBack({nullptr, temporaryIncomingMessage});
    ReadHeader();
  }

  void ReadHeader() {
    asioSocket.async_receive_from(
        asio::buffer(&temporaryIncomingMessage.header,
                     sizeof(rtype::network::MessageHeader<T>)),
        endpoint, [this](std::error_code ec, std::size_t bytesReceived) {
          if (!ec) {
            if (temporaryIncomingMessage.header.size > 0) {
              temporaryIncomingMessage.body.resize(
                  temporaryIncomingMessage.header.size);
              ReadBody();
            } else {
              AddMessageToIncomingQueue();
            }
          } else {
            std::cout << id << " : Read Header failed" << ec << std::endl;
            asioSocket.close();
          }
        });
  }

  void ReadBody() {
    asioSocket.async_receive_from(
        asio::buffer(temporaryIncomingMessage.body.data(),
                     temporaryIncomingMessage.body.size()),
        endpoint, [this](std::error_code ec, std::size_t bytesReceived) {
          if (!ec) {
            AddMessageToIncomingQueue();
          } else {
            std::cout << id << " : Read Body failed" << ec << std::endl;
            asioSocket.close();
          }
        });
  }

  //! Need to change the way I encrypt the message later
  uint64_t scramble(uint64_t n) {
    uint64_t result = n ^ 0xDEADBEEFC0DECAFE;
    result =
        (result & 0xF0F0F0F0DEADBEEF) << 4 | (result & 0xF0F0F0F00000000) >> 4;
    return result ^ 0xC0DEFACE12345678;
  }

  void WriteValidation() {
    asioSocket.async_send_to(
        asio::buffer(&handshakeOut, sizeof(uint64_t)), endpoint,
        [this](std::error_code ec, std::size_t bytesReceived) {
          if (!ec) {
            if (ownerType == actualOwner::CLIENT) {
              if (handshakeCheck == handshakeIn) {
                std::cout << "Handshake successful" << std::endl;
                ReadHeader();
              } else {
                std::cout << "Handshake failed" << std::endl;
                asioSocket.close();
              }
            } else {
              handshakeOut = scramble(handshakeIn);
              WriteValidation();
            }
          } else {
            std::cout << id << " : Write Validation failed" << ec << std::endl;
            asioSocket.close();
          }
        });
  }
};
} // namespace network
} // namespace rtype

#endif /* !NETWORKCONNECTION_HPP_ */
