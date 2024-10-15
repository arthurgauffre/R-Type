/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#pragma once

#include <AServer.hpp>
#include <CoreModule.hpp>
#include <NetworkMessagesCommunication.hpp>

namespace rtype
{
  namespace network
  {
    class Server : virtual public rtype::network::AServer<NetworkMessages>
    {
    public:
      Server(uint16_t port, std::shared_ptr<CoreModule> coreModule)
          : rtype::network::IServer<NetworkMessages>(),
            rtype::network::AServer<NetworkMessages>(port),
            _coreModule(coreModule)
      {
      }

      ~Server() {};

      virtual void init()
      {
        component::ComponentManager &componentManager = *_coreModule->getComponentManager();
        entity::EntityManager &entityManager = *_coreModule->getEntityManager();

        _coreModule->getSystemManager()->addSystem(componentManager, entityManager,
                                            "movement");
        _coreModule->getSystemManager()->addSystem(componentManager, entityManager,
                                            "collision");
        _coreModule->getSystemManager()->addSystem(componentManager, entityManager,
                                            "movement");
        _coreModule->getSystemManager()->addSystem(componentManager, entityManager,
                                            "health");
        _coreModule->getSystemManager()->addSystem(componentManager, entityManager,
                                            "movement");
      }

      virtual void run()
      {
        std::vector<std::string> msgToSend;
        sf::Clock clock;
        while (1)
        {
          float deltatime = clock.restart().asSeconds();
          this->Update(deltatime, false);
          _coreModule.get()->getSystemManager()->update(
              deltatime, _coreModule.get()->getEntityManager()->getEntities(), msgToSend);
        }
      }

    protected:
      virtual void OnMessageReceived(
          std::shared_ptr<rtype::network::NetworkConnection<NetworkMessages>>
              client,
          rtype::network::Message<NetworkMessages> &message)
      {
        std::cout << "Message received from client : " << client->GetId()
                  << std::endl;
        switch (message.header.id)
        {
        case NetworkMessages::ClientConnection:
        {
          std::cout << "Client connected : " << client->GetId() << std::endl;
        }
        break;
        case NetworkMessages::MessageAll:
        {
          rtype::network::Message<NetworkMessages> message;
          message.header.id = NetworkMessages::ServerMessage;
          message << client->GetId();
          SendMessageToAllClients(message, client);
        }
        break;
        case NetworkMessages::ServerPing:
        {
          std::cout << client->GetId() << " : Ping the server" << std::endl;
          client->Send(message);
        }
        break;
        }
      }

      virtual bool OnClientConnection(
          std::shared_ptr<rtype::network::NetworkConnection<NetworkMessages>>
              client)
      {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::ServerAcceptance;
        client->Send(message);
        message.header.id = NetworkMessages::createEntity;
        message.body.push_back(static_cast<u_int8_t>(NetworkMessages::createEntity));
        return true;
      }

      virtual void OnClientDisconnection(
          std::shared_ptr<rtype::network::NetworkConnection<NetworkMessages>>
              client)
      {
        // std::cout << "Client disconnected : " << client->GetId() << std::endl;
      }

      virtual void SendMessageToClient(
          const rtype::network::Message<NetworkMessages> &message,
          std::shared_ptr<rtype::network::NetworkConnection<NetworkMessages>>
              client) {}

    private:
      std::shared_ptr<CoreModule> _coreModule;
    };
  } // namespace network
} // namespace rtype

#endif /* !SERVER_HPP_ */
