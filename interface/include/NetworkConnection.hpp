/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** NetworkConnection
*/

#ifndef NETWORKCONNECTION_HPP_
#define NETWORKCONNECTION_HPP_

#pragma once

#include <NetworkMessagesCommunication.hpp>
#include <NetworkQueue.hpp>
#include <OwnedMessage.hpp>
#include <r-type/IServer.hpp>

std::ostream &operator<<(std::ostream &os,
                         const asio::ip::udp::socket &socket) {
  os << socket.local_endpoint().address().to_string() << ":"
     << socket.local_endpoint().port();
  return os;
}

std::ostream &operator<<(std::ostream &os,
                         const asio::ip::udp::endpoint &endpoint) {
  os << endpoint.address().to_string() << ":" << endpoint.port();
  return os;
}

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
      handshakeOut =
          uint64_t(std::chrono::system_clock::now().time_since_epoch().count());
      // assign the handsake check to the cryption method of the output
      handshakeCheck = scramble(handshakeOut);
    } else {
      // set the handshale output and input to 0
      handshakeOut = 0;
      handshakeIn = 0;
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

  void EstablishServerConnection() {
    if (ownerType == actualOwner::CLIENT) {
      ReadHeader();
      rtype::network::Message<NetworkMessages> message;
      message.header.id = NetworkMessages::ServerAcceptance;
      Send(message);
    }
  }

  bool IsConnected() const { return asioSocket.is_open(); }
  void Disconnect() {
    if (IsConnected()) {
      asio::post(asioContext, [this]() { asioSocket.close(); });
    }
  }

  void Send(const rtype::network::Message<T> &message) {
    asio::post(asioContext, [this, message]() {
      bool writingMessage = !queueOfOutgoingMessages.empty();
      queueOfOutgoingMessages.pushBack(message);
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

  rtype::network::ServerQueue<rtype::network::Message<T>>
      queueOfOutgoingMessages;
  rtype::network::Message<T> temporaryIncomingMessage;

  uint32_t id = 0;
  uint64_t handshakeOut = 0;
  uint64_t handshakeIn = 0;
  uint64_t handshakeCheck = 0;

private:
  void WriteHeader() {
    std::cout << "Sending to endpoint in the WriteHeader: " << endpoint
              << std::endl;
    asioSocket.async_send_to(
        asio::buffer(&queueOfOutgoingMessages.front().header,
                     sizeof(rtype::network::MessageHeader<T>)),
        endpoint, [this](std::error_code ec, std::size_t bytesReceived) {
          if (!ec) {
            // std::cout << "Header size in the WriteHeader" <<
            // queueOfOutgoingMessages.front().header.size() << std::endl;
            std::cout << "Body size in the WriteHeader : "
                      << queueOfOutgoingMessages.front().body.size()
                      << std::endl;
            if (queueOfOutgoingMessages.front().body.size() > 0) {
              WriteBody();
            } else {
              queueOfOutgoingMessages.popFront();
              std::cout << "Is the outgoing queue empty : "
                        << (queueOfOutgoingMessages.empty() ? "true" : "false")
                        << std::endl;
              if (!queueOfOutgoingMessages.empty()) {
                WriteHeader();
                std::cout << "Goes to the WriteHeader method" << std::endl;
              }
            }
          } else {
            std::cout << id << " : Write Header failed" << ec << std::endl;
            asioSocket.close();
          }
        });
  }

  void WriteBody() {
    std::cout << "Sending to endpoint in the WriteBody: " << endpoint
              << std::endl;

    asioSocket.async_send_to(
        asio::buffer(queueOfOutgoingMessages.front().body.data(),
                     queueOfOutgoingMessages.front().body.size()),
        endpoint, [this](std::error_code ec, std::size_t bytesReceived) {
          if (!ec) {
            queueOfOutgoingMessages.popFront();
            std::cout << "Is the outgoing queue empty : "
                      << (queueOfOutgoingMessages.empty() ? "true" : "false")
                      << std::endl;
            if (!queueOfOutgoingMessages.empty()) {
              WriteHeader();
              std::cout << "Goes to the WriteHeader method" << std::endl;
            }
          } else {
            std::cout << id << " : Write Body failed" << ec << std::endl;
            asioSocket.close();
          }
        });
  }

  void AddMessageToIncomingQueue() {
    // std::cout << "Message data : " << temporaryIncomingMessage.header.id <<
    // std::endl; std::cout << "Message data : " <<
    // temporaryIncomingMessage.body.data() << std::endl;
    if (ownerType == actualOwner::SERVER)
      queueOfIncomingMessages.pushBack(
          {this->shared_from_this(), temporaryIncomingMessage});
    else
      queueOfIncomingMessages.pushBack({nullptr, temporaryIncomingMessage});

    if (temporaryIncomingMessage.body.size() > 0) {

      std::cout << "Incoming message is : " << temporaryIncomingMessage
                << std::endl;
      std::cout << queueOfIncomingMessages.front().message << std::endl;
      // Deserialize PositionComponent from bytes and print the values
      // PositionComponent pos;

      // std::memcpy(&pos, temporaryIncomingMessage.body.data(),
      //             sizeof(PositionComponent));
      // std::cout << "PositionComponent x: " << pos.x << std::endl;
      // std::cout << "PositionComponent y: " << pos.y << std::endl;

      std::cout << "data : " << temporaryIncomingMessage.body.data()
                << std::endl;
    }

    ReadHeader();
  }

  void ReadHeader() {
    std::cout
        << "Reading the Header of the message at the start of the method...."
        << std::endl;
    asioSocket.async_receive_from(
        asio::buffer(&temporaryIncomingMessage.header,
                     sizeof(rtype::network::MessageHeader<T>)),
        endpoint, [this](std::error_code ec, std::size_t bytesReceived) {
          if (!ec) {
            std::cout << "Reading the Header of the message...." << std::endl;
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
    std::cout << "Reading the Body of the message...." << std::endl;
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
