/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AServer
*/

#ifndef ASERVER_HPP_
#define ASERVER_HPP_

#pragma once

#include <r-type/IServer.hpp>
#include <Error.hpp>
// #include <NetworkingCommon.hpp>
#include <NetworkQueue.hpp>
#include <OwnedMessage.hpp>

namespace rtype
{
    namespace network
    {
        template <typename T>
        class AServer : virtual public IServer<T>
        {
        public:
            AServer(uint16_t port) : rtype::network::IServer<T>(),
                                     asioSocket(asioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)),
                                     clientEndpoint(asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
            {
            }

            ~AServer() { Stop(); }

            bool Start()
            {
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

            void Stop()
            {
                asioContext.stop();

                if (contextThread.joinable())
                    contextThread.join();
                std::cout << "Server stopped !" << std::endl;
            }

            void WaitForMessage()
            {
                asioSocket.async_receive_from(
                    asio::buffer(bufferOfIncomingMessages.data(), bufferOfIncomingMessages.size()),
                    clientEndpoint, [this](std::error_code ec, std::size_t bytesReceived) {
                        if (!ec) {
                            std::cout << "New connection from: " << clientEndpoint << std::endl;

                            std::shared_ptr<NetworkConnection<T>> newConnection =
                                std::make_shared<NetworkConnection<T>>(
                                    NetworkConnection<T>::actualOwner::SERVER,
                                    asioContext, std::move(asioSocket), clientEndpoint,
                                    incomingMessages);
                            if (OnClientConnection(newConnection)) {
                                deqConnections.push_back(std::move(newConnection));
                                deqConnections.back()->EstablishClientConnection(this, actualId++);
                                std::cout << "[" << deqConnections.back()->GetId() << "] Connection approved" << std::endl;
                            } else {
                                std::cout << "Connection denied" << std::endl;
                            }
                        } else {
                            std::cout << "Error on connection" << ec.message() << std::endl;
                        }
                    }
                );
            }

            void SendMessageToClient(const Message<T> &message, std::shared_ptr<NetworkConnection<T>> client)
            {
                if (client && client->IsConnected()) {
                    client->Send(message);
                } else {
                    OnClientDisconnection(client);
                    client.reset();
                    deqConnections.erase(
                        std::remove(deqConnections.begin(), deqConnections.end(), client),
                        deqConnections.end()
                    );
                }
            }

            void SendMessageToAllClients(const rtype::network::Message<T> &message, std::shared_ptr<rtype::network::NetworkConnection<T>> clientToIgnore = nullptr)
            {
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
                        deqConnections.end()
                    );
                }
            }

            void Update(size_t maxMessages = -1, bool needToWait = false)
            {
                if (needToWait)
                    incomingMessages.wait();
                size_t messageCount = 0;
                while(messageCount < maxMessages && !incomingMessages.empty()) {
                    auto message = incomingMessages.popFront();
                    OnMessageReceived(message.remoteConnection, message.message);
                    messageCount++;
                }
            }

            virtual void OnClientValidated(std::shared_ptr<NetworkConnection<T>> client) {}


            rtype::network::ServerQueue<rtype::network::OwnedMessage<T>> incomingMessages;
            std::deque<std::shared_ptr<NetworkConnection<T>>> deqConnections;

            asio::io_context asioContext;
            std::thread contextThread;

            asio::ip::udp::socket asioSocket;
            asio::ip::udp::endpoint clientEndpoint;

            std::array<char, 1024> bufferOfIncomingMessages;
            uint32_t actualId = 0;

        protected:
            virtual void OnMessageReceived(std::shared_ptr<NetworkConnection<T>> client, Message<T> &message) {}
            virtual bool OnClientConnection(std::shared_ptr<rtype::network::NetworkConnection<T>> client) { return false; }
            virtual void OnClientDisconnection(std::shared_ptr<rtype::network::NetworkConnection<T>> client) {}

            };
        }
    }

#endif /* !ASERVER_HPP_ */
