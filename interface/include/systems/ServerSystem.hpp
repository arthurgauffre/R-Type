/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#pragma once

#include <r-type/IServer.hpp>

#include <components/DamageComponent.hpp>
#include <components/HealthComponent.hpp>
#include <components/HitBoxComponent.hpp>
#include <components/InputComponent.hpp>
#include <components/MusicComponent.hpp>
#include <components/ParentComponent.hpp>
#include <components/SizeComponent.hpp>
#include <components/SoundComponent.hpp>
#include <components/SpriteComponent.hpp>
#include <components/TextureComponent.hpp>
#include <components/TransformComponent.hpp>
#include <components/TypeComponent.hpp>
#include <components/VelocityComponent.hpp>
#include <components/WeaponComponent.hpp>
#include <components/CooldownComponent.hpp>
#include <components/SizeComponent.hpp>
#include <components/AIComponent.hpp>
#include <components/RectangleShapeComponent.hpp>
#include <components/OnClickComponent.hpp>

#include <managers/ComponentManager.hpp>
#include <managers/EntityManager.hpp>
#include <managers/SystemManager.hpp>

#include <NetworkMessagesCommunication.hpp>
#include <NetworkMessageFactory.hpp>
#include <NetworkConnection.hpp>
#include <NetworkQueue.hpp>
#include <NetworkMessage.hpp>
#include <Error.hpp>
#include <r-type/ASystem.hpp>
#include <ServerStatus.hpp>

#include <optional>

namespace rtype
{
  namespace network
  {
    template <typename T>
    class ServerSystem : virtual public rtype::network::IServer<NetworkMessages>,
                         virtual public ECS_system::ASystem
    {
    public:
      ServerSystem(component::ComponentManager &componentManager,
                   entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic, ECS_system::StringCom stringCom)
          : rtype::network::IServer<NetworkMessages>(), ECS_system::ASystem(
                                                            componentManager,
                                                            entityManager, graphic, stringCom),
            _componentManager(componentManager), _entityManager(entityManager), asioSocket(asioContext,
                                                                                           asio::ip::udp::endpoint(asio::ip::udp::v4(), 60000))
      {
        Start();
        for (int i = 0; i < 4; i++)
          _playerConnected.push_back(std::make_pair(false, -1));
      }

      ~ServerSystem() { Stop(); };

      void initialize() {};

      void handleComponents() {};

      void
      update(float deltaTime,
             std::vector<std::shared_ptr<entity::IEntity>> entities,
             std::vector<std::pair<Action, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<Scene> &sceneStatus)
      {
        *sceneStatus = Scene::GAME;
        sf::Clock clock;
        float deltatime = clock.restart().asSeconds();
        while (!msgToSend.empty())
        {
          std::pair<Action, size_t> msg = msgToSend.front();
          msgToSend.erase(msgToSend.begin());
          handleMsgToSend(msg);
        }
        sendAllEntitiesUpdateOrCreateToAllClient(nullptr);
        this->ServerUpdate(100, false);
        while (!_msgReceived.empty())
        {
          msgReceived.emplace_back(_msgReceived.back());
          _msgReceived.pop_back();
        }
      }

    protected:
      virtual void OnMessageReceived(
          std::shared_ptr<rtype::network::NetworkConnection<NetworkMessages>>
              client,
          rtype::network::Message<NetworkMessages> &message)
      {
        // std::cout << "Message received" << std::endl;
        switch (message.header.id)
        {
        case NetworkMessages::ClientConnection:
        {
          std::cout << "Client Connected in ServerSystem.hpp : " << client->GetId() << std::endl;
        }
        break;
        case NetworkMessages::MessageAll:
        {
          status = ServerStatus::SERVER_RECEIVING;
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
        case NetworkMessages::acknowledgementMesage:
        {
          // extract the content of the body's message
          if (!queueOfAckMessages.empty())
            queueOfAckMessages.pop_back();
        }
        break;
        default:
        {
          handleInputMessage(client, message);
        }
        }
      }

      void handleActionMessage(std::shared_ptr<rtype::network::NetworkConnection<NetworkMessages>> client,
                               Action action, size_t entityId)
      {
        switch (action)
        {
        case Action::MOVE_UP:
        {
          status = ServerStatus::SERVER_RECEIVING;
          _msgReceived.emplace_back(std::make_pair("moveUp", std::make_pair(entityId, client->GetId())));
        }
        break;
        case Action::MOVE_DOWN:
        {
          status = ServerStatus::SERVER_RECEIVING;
          _msgReceived.emplace_back(std::make_pair("moveDown", std::make_pair(entityId, client->GetId())));
        }
        break;
        case Action::MOVE_LEFT:
        {
          status = ServerStatus::SERVER_RECEIVING;
          _msgReceived.emplace_back(std::make_pair("moveLeft", std::make_pair(entityId, client->GetId())));
        }
        break;
        case Action::MOVE_RIGHT:
        {
          status = ServerStatus::SERVER_RECEIVING;
          _msgReceived.emplace_back(std::make_pair("moveRight", std::make_pair(entityId, client->GetId())));
        }
        break;
        case Action::SHOOT:
        {
          status = ServerStatus::SERVER_RECEIVING;
          // std::cout << "shoot" << std::endl;
          _msgReceived.emplace_back(std::make_pair("shoot", std::make_pair(entityId, client->GetId())));
        }
        break;
        case Action::PLAY:
        {
          _msgReceived.emplace_back(std::make_pair("play", std::make_pair(entityId, client->GetId())));
        }
        break;
        case Action::PROTANOPIA:
        {
          _msgReceived.emplace_back(std::make_pair("protanopia", std::make_pair(entityId, client->GetId())));
        }
        break;
        case Action::DEUTERANOPIA:
        {
          _msgReceived.emplace_back(std::make_pair("deuteranopia", std::make_pair(entityId, client->GetId())));
        }
        break;
        case Action::TRITANOPIA:
        {
          _msgReceived.emplace_back(std::make_pair("tritanopia", std::make_pair(entityId, client->GetId())));
        }
        break;
        case Action::CLEARFILTER:
        {
          _msgReceived.emplace_back(std::make_pair("clearFilter", std::make_pair(entityId, client->GetId())));
        }
        break;
        case Action::EXIT:
        {
          int numPlayer = 0;
          for (int i = 0; i < 4; i++)
          {
            if (_playerConnected[i].second == client->GetId())
            {
              numPlayer = i;
              _playerConnected[i].first = false;
              _playerConnected[i].second = -1;
              break;
            }
          }
          // wait for all the threads to finish before executing the disconnection of the client
          // std::this_thread::sleep_for(std::chrono::milliseconds(100));
          // std::cout << "WAITING FOR DISCONNECTION" << std::endl;
          _msgReceived.emplace_back(std::make_pair("clientDisconnection", std::make_pair(numPlayer, client->GetId())));
          // OnClientDisconnection(client);
          for (; incomingMessages.queueSize() > 0;) {
            incomingMessages.popBack();
          }
          // client->Disconnect();
          // client.reset();
          // return;
        }
        break;
        }
      }

      void handleInputMessage(
          std::shared_ptr<rtype::network::NetworkConnection<NetworkMessages>> client,
          rtype::network::Message<NetworkMessages> &message)
      {
        // print witch client send the message
        // std::cout << "Client " << client->GetId() << " send a message" << std::endl;
        // std::cout << "Handling input message" << std::endl;
        switch (message.header.id)
        {
        case NetworkMessages::action:
        {
          ActionMsg action;
          EntityId entity;
          std::memcpy(&entity, message.body.data(), sizeof(EntityId));
          std::memcpy(&action, message.body.data() + sizeof(EntityId),
                      sizeof(ActionMsg));
          handleActionMessage(client, action.action, entity.id);
        }
        break;
        default:
        {
          std::cout << "Unknown message" << std::endl;
        }
        }
      }

      virtual bool OnClientConnection(
          std::shared_ptr<rtype::network::NetworkConnection<NetworkMessages>>
              client)
      {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::ServerAcceptance;
        client->Send(message);

        return true;
      }


      virtual void OnClientDisconnection(
          std::shared_ptr<rtype::network::NetworkConnection<NetworkMessages>> client)
      {
        std::mutex connectionMutex;
        if (client)
        {
          std::lock_guard<std::mutex> lock(connectionMutex);
          auto it = std::remove_if(deqConnections.begin(), deqConnections.end(),
                                   [&](const auto &connection)
                                   {
                                     return connection->GetId() == client->GetId();
                                   });
          // deqConnections.erase(it, deqConnections.end());
          // client.reset();
          // return;
        }
      }

      void WaitForMessage()
      {
        asioSocket.async_receive_from(
            asio::buffer(bufferOfIncomingMessages.data(),
                         bufferOfIncomingMessages.size()),
            clientEndpoint, [this](std::error_code ec, std::size_t bytesReceived)
            {
          if (clientEndpoint.protocol() != asio::ip::udp::v4())
            return WaitForMessage();;
          if (!ec) {
            std::cout << "New connection from: " << clientEndpoint << std::endl;

            for (std::shared_ptr<NetworkConnection<T>> &connection :
                 deqConnections) {
              if (connection->GetEndpoint() == clientEndpoint) {
                std::cout << "Connection already exists" << std::endl;
                return;
              }
            }

            asio::ip::udp::socket newSocket(
                asioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0));

            std::shared_ptr<NetworkConnection<T>> newConnection =
                std::make_shared<NetworkConnection<T>>(
                    NetworkConnection<T>::actualOwner::SERVER, asioContext,
                    std::move(newSocket), clientEndpoint, incomingMessages);
            if (OnClientConnection(newConnection)) {
              deqConnections.push_back(std::move(newConnection));
              deqConnections.back()->EstablishClientConnection(this,
                                                               actualId++);
              std::cout << "[" << deqConnections.back()->GetId()
                        << "] Connection approved" << std::endl;
              int numPlayer = 0;
              for (int i = 0; i < 4; i++) {
                if (_playerConnected[i].first == true)
                  numPlayer++;
                else
                  break;
              }
              _playerConnected[numPlayer].first = true;
              _playerConnected[numPlayer].second = deqConnections.back()->GetId();
              sendAllEntitiesToClient(deqConnections.back(), deqConnections.back()->GetId());
              _msgReceived.emplace_back(std::make_pair("clientConnection", std::make_pair(numPlayer, deqConnections.back()->GetId())));
            } else {
              std::cout << "Connection denied" << std::endl;
            }
          } else {
            std::cout << "Error on connection" << ec.message() << std::endl;
          }
          WaitForMessage(); });
      }

      void sendAllEntitiesUpdateOrCreateToAllClient(std::shared_ptr<rtype::network::NetworkConnection<T>> clientToIgnore)
      {
        bool transform = false;
        for (auto &entity : _entityManager.getEntities())
        {
          if (entity->getCommunication() == entity::EntityCommunication::CREATE)
          {
            // status = ServerStatus::WAITING_FOR_MESSAGE;
            queueOfAckMessages.push_back(ServerStatus::WAITING_FOR_MESSAGE);

            if (entity->getNumClient() != -1)
            {
              for (int i = 0; i < deqConnections.size(); i++)
              {
                if (i == entity->getNumClient())
                  SendMessageToClient(networkMessageFactory.createEntityMsg(entity->getID(), entity->getSceneStatus(), entity->getNumClient()), deqConnections[i]);
              }
            }
            else
              SendMessageToAllClients(networkMessageFactory.createEntityMsg(entity->getID(), entity->getSceneStatus(), entity->getNumClient()), clientToIgnore);
            entity->setCommunication(entity::EntityCommunication::NONE);
          }
          else if (entity->getCommunication() == entity::EntityCommunication::UPDATE)
          {
            if (entity->getNumClient() != -1)
              SendMessageToClient(networkMessageFactory.updateEntityMsg(entity->getID(), entity->getSceneStatus(), entity->getNumClient()), clientToIgnore);
            else
              SendMessageToAllClients(networkMessageFactory.updateEntityMsg(entity->getID(), entity->getSceneStatus(), entity->getNumClient()), clientToIgnore);
            entity->setCommunication(entity::EntityCommunication::NONE);
          }
          else if (entity->getCommunication() == entity::EntityCommunication::DELETE)
          {
            // status = ServerStatus::WAITING_FOR_MESSAGE;
            queueOfAckMessages.push_back(ServerStatus::WAITING_FOR_MESSAGE);

            if (entity->getNumClient() != -1) {
              if (entity->getNumClient() < deqConnections.size())
                SendMessageToClient(networkMessageFactory.deleteEntityMsg(entity->getID()), deqConnections[entity->getNumClient()]);
            }
            else
              SendMessageToAllClients(networkMessageFactory.deleteEntityMsg(entity->getID()), clientToIgnore);
            _componentManager.removeAllComponents(entity->getID());
            _entityManager.removeEntity(entity->getID());
            return;
          }
          if (_componentManager.getComponent<component::SpriteComponent>(entity->getID()))
          {
            component::SpriteComponent *component =
                _componentManager.getComponent<component::SpriteComponent>(entity->getID());
            if (component->getCommunication() == component::ComponentCommunication::CREATE)
            {
              // queueOfAckMessages.push_back(ServerStatus::WAITING_FOR_MESSAGE);
              component->setCommunication(component::ComponentCommunication::NONE);
              SendMessageToAllClients(networkMessageFactory.createSpriteMsg(entity->getID(), component->getX(), component->getY()), clientToIgnore);
            }
            else if (component->getCommunication() == component::ComponentCommunication::UPDATE)
            {
              component->setCommunication(component::ComponentCommunication::NONE);
              SendMessageToAllClients(networkMessageFactory.updateSpriteMsg(entity->getID(), component->getX(), component->getY()), clientToIgnore);
            }
            else if (component->getCommunication() == component::ComponentCommunication::DELETE)
            {
              // queueOfAckMessages.push_back(ServerStatus::WAITING_FOR_MESSAGE);
              component->setCommunication(component::ComponentCommunication::NONE);
              SendMessageToAllClients(networkMessageFactory.deleteSpriteMsg(entity->getID()), clientToIgnore);
            }
          }
          if (_componentManager.getComponent<component::TextureComponent>(entity->getID()))
          {
            component::TextureComponent *component =
                _componentManager.getComponent<component::TextureComponent>(entity->getID());
            if (component->getCommunication() == component::ComponentCommunication::CREATE)
            {
              // queueOfAckMessages.push_back(ServerStatus::WAITING_FOR_MESSAGE);
              component->setCommunication(component::ComponentCommunication::NONE);
              auto textureKey = getKeyByValue(_stringCom.texturePath, component->getPath());
              if (textureKey)
                SendMessageToAllClients(networkMessageFactory.createTextureMsg(entity->getID(), *textureKey), clientToIgnore);
              else
                SendMessageToAllClients(networkMessageFactory.createTextureMsg(entity->getID(), TexturePath::Unknown), clientToIgnore);
            }
            else if (component->getCommunication() == component::ComponentCommunication::UPDATE)
            {
              component->setCommunication(component::ComponentCommunication::NONE);
              auto textureKey= getKeyByValue(_stringCom.texturePath, component->getPath());
              if (textureKey)
                SendMessageToAllClients(networkMessageFactory.updateTextureMsg(entity->getID(), *textureKey), clientToIgnore);
              else
                SendMessageToAllClients(networkMessageFactory.updateTextureMsg(entity->getID(), TexturePath::Unknown), clientToIgnore);
            }
            else if (component->getCommunication() == component::ComponentCommunication::DELETE)
            {
              // queueOfAckMessages.push_back(ServerStatus::WAITING_FOR_MESSAGE);
              component->setCommunication(component::ComponentCommunication::NONE);
              SendMessageToAllClients(networkMessageFactory.deleteTextureMsg(entity->getID()), clientToIgnore);
            }
          }
          if (_componentManager.getComponent<component::TransformComponent>(entity->getID()))
          {
            component::TransformComponent *component =
                _componentManager.getComponent<component::TransformComponent>(entity->getID());
            if (component->getCommunication() == component::ComponentCommunication::CREATE)
            {
              // queueOfAckMessages.push_back(ServerStatus::WAITING_FOR_MESSAGE);
              component->setCommunication(component::ComponentCommunication::NONE);
              SendMessageToAllClients(networkMessageFactory.createTransformMsg(entity->getID(), component->getPosition().first, component->getPosition().second, component->getScale().first, component->getScale().second, component->getRotation()), clientToIgnore);
            }
            else if (component->getCommunication() == component::ComponentCommunication::UPDATE)
            {
              if (frequencyClock.getElapsedTime().asSeconds() > 0.2)
              {
                component->setCommunication(component::ComponentCommunication::NONE);
                SendMessageToAllClients(networkMessageFactory.updateTransformMsg(entity->getID(), component->getPosition().first, component->getPosition().second, component->getScale().first, component->getScale().second, component->getRotation()), clientToIgnore);
                transform = true;
              }
            }
            else if (component->getCommunication() == component::ComponentCommunication::DELETE)
            {
              // queueOfAckMessages.push_back(ServerStatus::WAITING_FOR_MESSAGE);
              component->setCommunication(component::ComponentCommunication::NONE);
              SendMessageToAllClients(networkMessageFactory.deleteTransformMsg(entity->getID()), clientToIgnore);
            }
          }
          if (_componentManager.getComponent<component::VelocityComponent>(entity->getID()))
          {
            component::VelocityComponent *component =
                _componentManager.getComponent<component::VelocityComponent>(entity->getID());
            if (component->getCommunication() == component::ComponentCommunication::CREATE)
            {
              // queueOfAckMessages.push_back(ServerStatus::WAITING_FOR_MESSAGE);
              component->setCommunication(component::ComponentCommunication::NONE);
              SendMessageToAllClients(networkMessageFactory.createVelocityMsg(entity->getID(), component->getVelocity().first, component->getVelocity().second, component->getActualVelocity().first, component->getActualVelocity().second), clientToIgnore);
            }
            else if (component->getCommunication() == component::ComponentCommunication::UPDATE)
            {
              component->setCommunication(component::ComponentCommunication::NONE);
              SendMessageToAllClients(networkMessageFactory.updateVelocityMsg(entity->getID(), component->getVelocity().first, component->getVelocity().second, component->getActualVelocity().first, component->getActualVelocity().second), clientToIgnore);
            }
            else if (component->getCommunication() == component::ComponentCommunication::DELETE)
            {
              // queueOfAckMessages.push_back(ServerStatus::WAITING_FOR_MESSAGE);
              component->setCommunication(component::ComponentCommunication::NONE);
              SendMessageToAllClients(networkMessageFactory.deleteVelocityMsg(entity->getID()), clientToIgnore);
            }
          }
          if (_componentManager.getComponent<component::InputComponent>(entity->getID()))
          {
            component::InputComponent *component =
                _componentManager.getComponent<component::InputComponent>(entity->getID());
            for (int i = 0; i < deqConnections.size(); i++)
            {
              if (deqConnections[i]->GetId() == component->getNumClient())
              {

                if (component->getCommunication() == component::ComponentCommunication::CREATE)
                {
                  std::cout << "ON CREATE" << std::endl;

                  queueOfAckMessages.push_back(ServerStatus::WAITING_FOR_MESSAGE);

                  component->setCommunication(component::ComponentCommunication::STANDBY);
                  std::cout << "SENDING INPUT MSG TO CLIENT" << std::endl;
                  SendMessageToClient(networkMessageFactory.createInputMsg(entity->getID(), component->getNumClient()), deqConnections[i]);
                }
                else if (component->getCommunication() == component::ComponentCommunication::STANDBY)
                {
                  if (queueOfAckMessages.empty())
                  {
                    component->setCommunication(component::ComponentCommunication::NONE);
                    for (auto &bind : component->getKeyBindings())
                    {
                      BindKey input = {bind.second, bind.first};
                      SendMessageToClient(networkMessageFactory.updateInputMsg(entity->getID(), input), deqConnections[i]);
                    }
                  // return;
                  }
                }
                else if (component->getCommunication() == component::ComponentCommunication::UPDATE)
                {
                  component->setCommunication(component::ComponentCommunication::NONE);
                  for (auto &bind : component->getKeyBindings())
                  {
                    BindKey input = {bind.second, bind.first};
                    SendMessageToClient(networkMessageFactory.updateInputMsg(entity->getID(), input), deqConnections[i]);
                  }
                }
                else if (component->getCommunication() == component::ComponentCommunication::DELETE)
                {
                  component->setCommunication(component::ComponentCommunication::NONE);
                  SendMessageToClient(networkMessageFactory.deleteInputMsg(entity->getID()), deqConnections[i]);
                }
              }
            }
          }
          if (_componentManager.getComponent<component::TypeComponent>(entity->getID()))
          {
            component::TypeComponent *component =
                _componentManager.getComponent<component::TypeComponent>(entity->getID());
            if (component->getCommunication() == component::ComponentCommunication::CREATE)
            {
              queueOfAckMessages.push_back(ServerStatus::WAITING_FOR_MESSAGE);
              component->setCommunication(component::ComponentCommunication::NONE);
              SendMessageToAllClients(networkMessageFactory.createTypeMsg(entity->getID(), component->getType()), clientToIgnore);
            }
            else if (component->getCommunication() == component::ComponentCommunication::UPDATE)
            {
              component->setCommunication(component::ComponentCommunication::NONE);
              SendMessageToAllClients(networkMessageFactory.updateTypeMsg(entity->getID(), component->getType()), clientToIgnore);
            }
            else if (component->getCommunication() == component::ComponentCommunication::DELETE)
            {
              // queueOfAckMessages.push_back(ServerStatus::WAITING_FOR_MESSAGE);
              component->setCommunication(component::ComponentCommunication::NONE);
              SendMessageToAllClients(networkMessageFactory.deleteTypeMsg(entity->getID()), clientToIgnore);
            }
          }
          if (_componentManager.getComponent<component::SizeComponent>(entity->getID()))
          {
            component::SizeComponent *component =
                _componentManager.getComponent<component::SizeComponent>(entity->getID());
            if (component->getCommunication() == component::ComponentCommunication::CREATE)
            {
              // queueOfAckMessages.push_back(ServerStatus::WAITING_FOR_MESSAGE);
              component->setCommunication(component::ComponentCommunication::NONE);
              SendMessageToAllClients(networkMessageFactory.createSizeMsg(entity->getID(), component->getSize().first, component->getSize().second), clientToIgnore);
            }
            else if (component->getCommunication() == component::ComponentCommunication::UPDATE)
            {
              component->setCommunication(component::ComponentCommunication::NONE);
              SendMessageToAllClients(networkMessageFactory.updateSizeMsg(entity->getID(), component->getSize().first, component->getSize().second), clientToIgnore);
            }
            else if (component->getCommunication() == component::ComponentCommunication::DELETE)
            {
              // queueOfAckMessages.push_back(ServerStatus::WAITING_FOR_MESSAGE);
              component->setCommunication(component::ComponentCommunication::NONE);
              SendMessageToAllClients(networkMessageFactory.deleteSizeMsg(entity->getID()), clientToIgnore);
            }
          }
          if (_componentManager.getComponent<component::AIComponent>(entity->getID()))
          {
            component::AIComponent *component =
                _componentManager.getComponent<component::AIComponent>(entity->getID());
            if (component->getCommunication() == component::ComponentCommunication::CREATE)
            {
              // queueOfAckMessages.push_back(ServerStatus::WAITING_FOR_MESSAGE);
              component->setCommunication(component::ComponentCommunication::NONE);
              SendMessageToAllClients(networkMessageFactory.createAIMsg(entity->getID(), component->getType()), clientToIgnore);
            }
            else if (component->getCommunication() == component::ComponentCommunication::UPDATE)
            {
              component->setCommunication(component::ComponentCommunication::NONE);
              SendMessageToAllClients(networkMessageFactory.updateAIMsg(entity->getID(), component->getType()), clientToIgnore);
            }
            else if (component->getCommunication() == component::ComponentCommunication::DELETE)
            {
              // queueOfAckMessages.push_back(ServerStatus::WAITING_FOR_MESSAGE);
              component->setCommunication(component::ComponentCommunication::NONE);
              SendMessageToAllClients(networkMessageFactory.deleteAIMsg(entity->getID()), clientToIgnore);
            }
          }
          if (_componentManager.getComponent<component::RectangleShapeComponent>(entity->getID()))
          {
            component::RectangleShapeComponent *component =
                _componentManager.getComponent<component::RectangleShapeComponent>(entity->getID());
            if (component->getCommunication() == component::ComponentCommunication::CREATE)
            {
              status = ServerStatus::WAITING_FOR_MESSAGE;
              component->setCommunication(component::ComponentCommunication::NONE);
              SendMessageToAllClients(networkMessageFactory.createRectangleShapeMsg(entity->getID(), component->getX(), component->getY(), component->getHeight(), component->getWidth(), component->getColor()), clientToIgnore);
            }
            else if (component->getCommunication() == component::ComponentCommunication::UPDATE)
            {
              component->setCommunication(component::ComponentCommunication::NONE);
              SendMessageToAllClients(networkMessageFactory.updateRectangleShapeMsg(entity->getID(), component->getX(), component->getY(), component->getHeight(), component->getWidth(), component->getColor()), clientToIgnore);
            }
            else if (component->getCommunication() == component::ComponentCommunication::DELETE)
            {
              component->setCommunication(component::ComponentCommunication::NONE);
              SendMessageToAllClients(networkMessageFactory.deleteRectangleShapeMsg(entity->getID()), clientToIgnore);
            }
          }
          if (_componentManager.getComponent<component::OnClickComponent>(entity->getID()))
          {
            component::OnClickComponent *component =
                _componentManager.getComponent<component::OnClickComponent>(entity->getID());
            for (int i = 0; i < deqConnections.size(); i++)
            {
              if (deqConnections[i]->GetId() == component->getNumClient())
              {
                if (component->getCommunication() == component::ComponentCommunication::CREATE)
                {
                  queueOfAckMessages.push_back(ServerStatus::WAITING_FOR_MESSAGE);

                  component->setCommunication(component::ComponentCommunication::STANDBY);
                  SendMessageToClient(networkMessageFactory.createOnClickMsg(entity->getID(), component->getNumClient(), component->getAction()), deqConnections[i]);
                }
                else if (component->getCommunication() == component::ComponentCommunication::STANDBY)
                {
                  if (queueOfAckMessages.empty())
                  {
                    component->setCommunication(component::ComponentCommunication::NONE);
                    SendMessageToClient(networkMessageFactory.updateOnClickMsg(entity->getID(), component->getAction()), deqConnections[i]);
                    return;
                  }
                }
                else if (component->getCommunication() == component::ComponentCommunication::UPDATE)
                {
                  component->setCommunication(component::ComponentCommunication::NONE);
                  SendMessageToClient(networkMessageFactory.updateOnClickMsg(entity->getID(), component->getAction()), deqConnections[i]);
                }
                else if (component->getCommunication() == component::ComponentCommunication::DELETE)
                {
                  status = ServerStatus::SERVER_RECEIVING;
                  component->setCommunication(component::ComponentCommunication::NONE);
                  SendMessageToClient(networkMessageFactory.deleteOnClickMsg(entity->getID()), deqConnections[i]);
                }
              }
            }
          }
          if (_componentManager.getComponent<component::TextComponent>(entity->getID()))
          {
            component::TextComponent *component =
                _componentManager.getComponent<component::TextComponent>(entity->getID());
            if (component->getCommunication() == component::ComponentCommunication::CREATE)
            {
              status = ServerStatus::WAITING_FOR_MESSAGE;
              auto textFontKey = getKeyByValue(_stringCom.textFont, component->getFont());
              auto textStringKey = getKeyByValue(_stringCom.textString, component->getText());
              if (textFontKey && textStringKey)
              {
                component->setCommunication(component::ComponentCommunication::NONE);
                SendMessageToAllClients(networkMessageFactory.createTextMsg(entity->getID(), component->getX(), component->getY(), *textFontKey, *textStringKey, component->getSize(), component->getColor()), clientToIgnore);
              }
              else
              {
                component->setCommunication(component::ComponentCommunication::NONE);
                SendMessageToAllClients(networkMessageFactory.createTextMsg(entity->getID(), component->getX(), component->getY(), TextFont::Unknown, TextString::Unknown, component->getSize(), component->getColor()), clientToIgnore);
              }
            }
            else if (component->getCommunication() == component::ComponentCommunication::UPDATE)
            {
              component->setCommunication(component::ComponentCommunication::NONE);
              auto textFontKey = getKeyByValue(_stringCom.textFont, component->getFont());
              auto textStringKey = getKeyByValue(_stringCom.textString, component->getText());
              if (textFontKey && textStringKey)
              {
                component->setCommunication(component::ComponentCommunication::NONE);
                SendMessageToAllClients(networkMessageFactory.updateTextMsg(entity->getID(), component->getX(), component->getY(), *textFontKey, *textStringKey, component->getSize(), component->getColor()), clientToIgnore);
              }
              else
              {
                component->setCommunication(component::ComponentCommunication::NONE);
                SendMessageToAllClients(networkMessageFactory.updateTextMsg(entity->getID(), component->getX(), component->getY(), TextFont::Unknown, TextString::Unknown, component->getSize(), component->getColor()), clientToIgnore);
              }
            }
            else if (component->getCommunication() == component::ComponentCommunication::DELETE)
            {
              component->setCommunication(component::ComponentCommunication::NONE);
              SendMessageToAllClients(networkMessageFactory.deleteTextMsg(entity->getID()), clientToIgnore);
            }
          }
        }
        if (transform)
        {
          frequencyClock.restart();
        }
      }

      void sendAllEntitiesToClient(std::shared_ptr<NetworkConnection<T>> client, int numClient)
      {
        if (client->IsConnected() == false)
        {
          std::cout << "Client is not connected" << std::endl;
        }
        else
        {
          std::cout << "Client is connected" << std::endl;
        }
        for (auto &entity : _entityManager.getEntities())
        {
          if (entity->getNumClient() != -1 && entity->getNumClient() != numClient)
            continue;
          SendMessageToClient(
              networkMessageFactory.createEntityMsg(entity->getID(), entity->getSceneStatus(), entity->getNumClient()), client);
          if (_componentManager.getComponent<component::SpriteComponent>(entity->getID()))
          {
            component::SpriteComponent *component =
                _componentManager.getComponent<component::SpriteComponent>(entity->getID());
            SendMessageToClient(
                networkMessageFactory.createSpriteMsg(
                    entity->getID(), component->getX(), component->getY()),
                client);
          }
          if (_componentManager.getComponent<component::TextureComponent>(entity->getID()))
          {
            component::TextureComponent *component =
                _componentManager.getComponent<component::TextureComponent>(entity->getID());
            auto textureKey = getKeyByValue(_stringCom.texturePath, component->getPath());
            if (textureKey)
              SendMessageToClient(networkMessageFactory.createTextureMsg(entity->getID(), *textureKey), client);
            else
              SendMessageToClient(networkMessageFactory.createTextureMsg(entity->getID(), TexturePath::Unknown), client);
          }
          if (_componentManager.getComponent<component::TextComponent>(entity->getID()))
          {
            component::TextComponent *component =
                _componentManager.getComponent<component::TextComponent>(entity->getID());
            auto textFontKey = getKeyByValue(_stringCom.textFont, component->getFont());
            auto textStringKey = getKeyByValue(_stringCom.textString, component->getText());
            if (textFontKey && textStringKey)
            {
              SendMessageToClient(networkMessageFactory.createTextMsg(entity->getID(), component->getX(), component->getY(), *textFontKey, *textStringKey, component->getSize(), component->getColor()), client);
            }
            else
            {
              SendMessageToClient(networkMessageFactory.createTextMsg(entity->getID(), component->getX(), component->getY(), TextFont::Unknown, TextString::Unknown, component->getSize(), component->getColor()), client);
            }
          }
          if (_componentManager.getComponent<component::TransformComponent>(entity->getID()))
          {
            component::TransformComponent *component =
                _componentManager.getComponent<component::TransformComponent>(entity->getID());
            SendMessageToClient(networkMessageFactory.createTransformMsg(
                                    entity->getID(), component->getPosition().first,
                                    component->getPosition().second,
                                    component->getScale().first,
                                    component->getScale().second, component->getRotation()),
                                client);
          }
          if (_componentManager.getComponent<component::VelocityComponent>(entity->getID()))
          {
            component::VelocityComponent *component =
                _componentManager.getComponent<component::VelocityComponent>(entity->getID());
            if (component->getCommunication() != component::ComponentCommunication::SERVERONLY)
            {

              SendMessageToClient(networkMessageFactory.createVelocityMsg(
                                      entity->getID(), component->getVelocity().first,
                                      component->getVelocity().second, component->getActualVelocity().first, component->getActualVelocity().second),
                                  client);
            }
          }
          if (_componentManager.getComponent<component::HealthComponent>(entity->getID()))
          {
            component::HealthComponent *component =
                _componentManager.getComponent<component::HealthComponent>(entity->getID());
            SendMessageToClient(networkMessageFactory.createHealthMsg(
                                    entity->getID(), component->getHealth()),
                                client);
          }
          if (_componentManager.getComponent<component::DamageComponent>(entity->getID()))
          {
            component::DamageComponent *component =
                _componentManager.getComponent<component::DamageComponent>(entity->getID());
            SendMessageToClient(networkMessageFactory.createDamageMsg(
                                    entity->getID(), component->getDamage()),
                                client);
          }
          if (_componentManager.getComponent<component::HitBoxComponent>(entity->getID()))
          {
            component::HitBoxComponent *component =
                _componentManager.getComponent<component::HitBoxComponent>(entity->getID());
            SendMessageToClient(
                networkMessageFactory.createHitboxMsg(
                    entity->getID(), component->getHeight(), component->getWidth()),
                client);
          }
          if (_componentManager.getComponent<component::ParentComponent>(entity->getID()))
          {
            component::ParentComponent *component =
                _componentManager.getComponent<component::ParentComponent>(entity->getID());
            SendMessageToClient(networkMessageFactory.createParentMsg(
                                    entity->getID(), component->getParentID()),
                                client);
          }
          if (_componentManager.getComponent<component::InputComponent>(entity->getID()))
          {
            component::InputComponent *component =
                _componentManager.getComponent<component::InputComponent>(entity->getID());
            if (numClient == component->getNumClient())
            {
              SendMessageToClient(networkMessageFactory.createInputMsg(entity->getID(), component->getNumClient()), client);
              for (auto &bind : component->getKeyBindings())
              {
                BindKey input = {bind.second, bind.first};
                SendMessageToClient(networkMessageFactory.updateInputMsg(entity->getID(), input), client);
              }
            }
          }
          if (_componentManager.getComponent<component::TypeComponent>(entity->getID()))
          {
            component::TypeComponent *component =
                _componentManager.getComponent<component::TypeComponent>(entity->getID());
            SendMessageToClient(networkMessageFactory.createTypeMsg(
                                    entity->getID(), component->getType()),
                                client);
          }
          if (_componentManager.getComponent<component::AIComponent>(entity->getID()))
          {
            component::AIComponent *component =
                _componentManager.getComponent<component::AIComponent>(entity->getID());
            SendMessageToClient(networkMessageFactory.createAIMsg(
                                    entity->getID(), component->getType()),
                                client);
          }
          if (_componentManager.getComponent<component::SizeComponent>(entity->getID()))
          {
            component::SizeComponent *component =
                _componentManager.getComponent<component::SizeComponent>(entity->getID());
            SendMessageToClient(networkMessageFactory.createSizeMsg(
                                    entity->getID(), component->getSize().first, component->getSize().second),
                                client);
          }
          if (_componentManager.getComponent<component::RectangleShapeComponent>(entity->getID()))
          {
            component::RectangleShapeComponent *component =
                _componentManager.getComponent<component::RectangleShapeComponent>(entity->getID());
            SendMessageToClient(networkMessageFactory.createRectangleShapeMsg(
                                    entity->getID(), component->getX(), component->getY(), component->getWidth(), component->getHeight(), component->getColor()),
                                client);
          }
          if (_componentManager.getComponent<component::OnClickComponent>(entity->getID()))
          {
            component::OnClickComponent *component =
                _componentManager.getComponent<component::OnClickComponent>(entity->getID());
            if (numClient == component->getNumClient())
            {
              SendMessageToClient(networkMessageFactory.createOnClickMsg(entity->getID(), component->getNumClient(), component->getAction()), client);
            }
          }
        }
      }

      bool Start()
      {
        try
        {
          WaitForMessage();

          contextThread = std::thread([this]()
                                      { asioContext.run(); });
        }
        catch (rtype::RtypeException &e)
        {
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

      void SendMessageToClient(const Message<T> &message,
                               std::shared_ptr<NetworkConnection<T>> client)
      {
        if (client && client->IsConnected())
        {
          // std::cout << "Sending message to client" << std::endl;
          client->Send(message);
        }
        else
        {
          OnClientDisconnection(client);
          // client.reset();
          // deqConnections.erase(
          //     std::remove(deqConnections.begin(), deqConnections.end(), client),
          //     deqConnections.end());
        }
      }

      void SendMessageToAllClients(
          const rtype::network::Message<T> &message,
          std::shared_ptr<rtype::network::NetworkConnection<T>> clientToIgnore =
              nullptr)
      {
        bool invalidClientExists = false;
        for (auto &client : deqConnections)
        {
          if (client && client->IsConnected())
          {
            if (client != clientToIgnore)
            {
              client->Send(message);
            }
          }
          else
          {
            OnClientDisconnection(client);
            // client.reset();
            invalidClientExists = true;
          }
        }
        if (invalidClientExists)
        {
          deqConnections.erase(
              std::remove(deqConnections.begin(), deqConnections.end(), nullptr),
              deqConnections.end());
        }
      }

      void ServerUpdate(size_t maxMessages = -1, bool needToWait = false)
      {
        if (needToWait == true)
          incomingMessages.wait();
        size_t messageCount = 0;
        while (messageCount < maxMessages && !incomingMessages.empty())
        {
          auto msg = incomingMessages.popFront();
          auto originalQueueSize = queueOfAckMessages.size();
          // OnMessageReceived(msg.remoteConnection, msg.message);
          if (queueOfAckMessages.empty() == false) {
            OnMessageReceived(msg.remoteConnection, msg.message);
            if (originalQueueSize == queueOfAckMessages.size())
              incomingMessages.pushBack(msg);
          } else {
            OnMessageReceived(msg.remoteConnection, msg.message);
          }
          messageCount++;
        }
      }

      virtual void OnClientValidated(std::shared_ptr<NetworkConnection<T>> client)
      {
      }

      template <typename KeyType, typename ValueType>
      std::optional<KeyType> getKeyByValue(const std::unordered_map<KeyType, ValueType> &map, const ValueType &value)
      {
        for (const auto &[key, val] : map)
        {
          if (val == value)
          {
            return key;
          }
        }
        return std::nullopt;
      }

      void handleMsgToSend(std::pair<Action, size_t> msgToSend)
      {
        std::cout << "Handling message to send" << std::endl;
        if (msgToSend.first == Action::MENU)
          SendMessageToClient(networkMessageFactory.createMenuMsg(), deqConnections[msgToSend.second]);
        else if (msgToSend.first == Action::GAME)
          SendMessageToClient(networkMessageFactory.createGameMsg(), deqConnections[msgToSend.second]);
        // else if (msgToSend.first == Action::SETTINGS)
        // SendMessageToClient(networkMessageFactory.createSettingsMsg(), deqConnections[msgToSend.second]);
        // else if (msgToSend.first == Action::EXIT)
        //   SendMessageToClient(networkMessageFactory.createExitMsg(), deqConnections[msgToSend.second]);
      }

      rtype::network::ServerQueue<rtype::network::OwnedMessage<T>> incomingMessages;
      std::deque<std::shared_ptr<NetworkConnection<T>>> deqConnections;

      asio::io_context asioContext;
      std::thread contextThread;

      asio::ip::udp::socket asioSocket;
      asio::ip::udp::endpoint clientEndpoint;

      NetworkMessageFactory networkMessageFactory;
      std::array<char, 1024> bufferOfIncomingMessages;
      uint32_t actualId = 0;
      ServerStatus status;
      std::vector<ServerStatus> queueOfAckMessages;
      // int nbOfAckMessages = 0;

      std::vector<std::pair<std::string, std::pair<size_t, size_t>>> _msgReceived;

    private:
      std::vector<std::pair<bool, int>> _playerConnected;
      component::ComponentManager &_componentManager;
      entity::EntityManager &_entityManager;
      sf::Clock frequencyClock;
    };
  } // namespace network
} // namespace rtype

#endif /* !SERVER_HPP_ */
