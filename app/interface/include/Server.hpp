/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#define ASIO_STANDALONE

#include <cstdint>
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

#include <NetworkMessage.hpp>
#include <NetworkQueue.hpp>
#include <NetworkConnection.hpp>
#include <OwnedMessage.hpp>
#include <Error.hpp>

namespace rytpe {
    namespace network {
        template <typename T>
        class Server {
            public:
                Server(){};
                Server(uint16_t port) : asioSocket(asioContext,
                asio::ip::udp::endpoint(asio::ip::udp::v4(), port)){}

                ~Server(){};

                bool Start() {
                    try {
                        contextThread = std::thread([this]() { asioContext.run(); });

                        WaitForMessage();

                        std::cout << "Server started !" << std::endl;

                        return true;

                    } catch (rtype::ServerException &e) {

                        std::cerr << "Server exception :" << e.what() << std::endl;
                        return false;
                    }
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
                        asio::buffer(bufferOfIncomingMessages), endpoint,
                        [this](std::error_code ec, std::size_t bytesReceived)
                        {
                            if (bytesReceived && !ec) {
                                std::cout << "Received message from: " << endpoint << std::endl;
                                rtype::network::Message<T> currentMessage;

                                std::memcpy(&currentMessage, bufferOfIncomingMessages.data(), bytesReceived)

                                incomingMessages.pushBack({currentMessage, endpoint });
                                OnMessageReceived(endpoint, message)

                                WaitForMessage();
                            }

                        }
                    )
                }

                void SendMessageToClient(const rtype::network::Message<T> &message,
                const asio::ip::udp::endpoint &clientEndpoint)
                {
                    asioSocket.async_send_to(
                        asio::buffer(&message, message.size()), clientEndpoint,
                        [](std::error_code ec, std::size_t bytesSent)
                        {
                            if (ec)
                                std::cerr << "Error sending message to client: " << ec.message() << std::endl;
                        }
                    );
                }

                void SendMessageToAllClients(const rtype::network::Message<T> &message)
                {
                    for (auto &clientAddr : clientEndpoints)
                        SendMessageToClient(message, clientAddr);
                }

                void Update(bool needToWait = false)
                {
                    if (needToWait)
                        incomingMessages.wait();

                    size_t messageCount = 0;
                    while (!incomingMessages.empty())
                    {
                        auto message = incomingMessages.popFront();
                        OnMessageReceived(message.endpoint, message.message);
                        messageCount++;
                    }
                }

                virtual void OnClientValidated(std::shared_ptr<rtype::network::NetworkConnection<T>> client)
                {
                }

            protected:


                virtual void OnMessageReceived(
                    std::shared_ptr<NetworkConnection<T>> client,
                    rtype::network::Message<T> &message)
                {
                }

                virtual void OnClientConnection(std::shared_ptr<rtype::network::NetworkConnection<T>> client)
                {
                    return false;
                }

                virtual void OnClientDisconnection(std::shared_ptr<rtype::network::NetworkConnection<T>> client)
                {
                }


                std::array<char, 1024> bufferOfIncomingMessages;

                asio::io_context asioContext;
                asio::ip::udp::socket asioSocket;
                asio::ip::udp::endpoint endpoint;
                std::thread contextThread;

                rtype::network::ServerQueue<rtype::network::OwnedMessage<T>> incomingMessages;
                std::vector<asio::ip::udp::endpoint>  clientEndpoints;
        };
    }
}

#endif /* !SERVER_HPP_ */
