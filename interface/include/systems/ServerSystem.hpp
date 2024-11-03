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

#include <Clock.hpp>

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
                   entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic, std::shared_ptr<IAudio> audio, ECS_system::StringCom stringCom)
          : rtype::network::IServer<NetworkMessages>(), ECS_system::ASystem(
                                                            componentManager,
                                                            entityManager, graphic, audio, stringCom),
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

      void ackMessageReceivedAction(EntityId receivedEntity, NetworkMessages messageType)
      {
        size_t originalQueueSize = queueOfAckMessages.size();
        queueOfAckMessages.erase(std::remove_if(queueOfAckMessages.begin(), queueOfAckMessages.end(), [receivedEntity](const std::pair<ServerStatus, uint32_t> &ackMessage)
                                                { return ackMessage.second == receivedEntity.id; }),
                                 queueOfAckMessages.end());
        if (queueOfAckMessages.size() != originalQueueSize && queueOfOutgoingMessages.size() > 0)
        {

          queueOfOutgoingMessages.erase(std::remove_if(queueOfOutgoingMessages.begin(), queueOfOutgoingMessages.end(),
                                                       [receivedEntity, messageType](const std::pair<rtype::network::Message<NetworkMessages>, std::pair<uint32_t, int>> &outgoingMessage)
                                                       {
                                                         return outgoingMessage.first.header.id == messageType && outgoingMessage.second.first == receivedEntity.id;
                                                       }),
                                        queueOfOutgoingMessages.end());
        }
      }

      void
      update(float deltaTime,
             std::vector<std::shared_ptr<entity::IEntity>> entities,
             std::vector<std::pair<Action, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<Scene> &sceneStatus)
      {
        *sceneStatus = Scene::GAME;
        rtype::Clock clock;
        float deltatime = clock.restart();
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
        switch (message.header.id)
        {
        case NetworkMessages::ClientConnection:
        {
          std::cout << "Client Connected in ServerSystem.hpp : " << client->GetId() << std::endl;
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
          client->Send(message);
        }
        break;
        case NetworkMessages::acknowledgementMesageToCreateEntity:
        {

          EntityId receivedEntity;
          std::memcpy(&receivedEntity, message.body.data(), sizeof(EntityId));
          ackMessageReceivedAction(receivedEntity, NetworkMessages::createEntity);
        }
        break;
        case NetworkMessages::acknowledgementMesageToCreateInput:
        {
          EntityId receivedEntity;
          std::memcpy(&receivedEntity, message.body.data(), sizeof(EntityId));
          ackMessageReceivedAction(receivedEntity, NetworkMessages::createInput);
        }
        break;
        case NetworkMessages::acknowledgementMesageToCreateOnClick:
        {
          EntityId receivedEntity;
          std::memcpy(&receivedEntity, message.body.data(), sizeof(EntityId));
          ackMessageReceivedAction(receivedEntity, NetworkMessages::createOnClick);
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
          _msgReceived.emplace_back(std::make_pair("moveUp", std::make_pair(entityId, client->GetId())));
        }
        break;
        case Action::MOVE_DOWN:
        {
          _msgReceived.emplace_back(std::make_pair("moveDown", std::make_pair(entityId, client->GetId())));
        }
        break;
        case Action::MOVE_LEFT:
        {
          _msgReceived.emplace_back(std::make_pair("moveLeft", std::make_pair(entityId, client->GetId())));
        }
        break;
        case Action::MOVE_RIGHT:
        {
          _msgReceived.emplace_back(std::make_pair("moveRight", std::make_pair(entityId, client->GetId())));
        }
        break;
        case Action::SHOOT:
        {
          _msgReceived.emplace_back(std::make_pair("shoot", std::make_pair(entityId, client->GetId())));
        }
        break;
        case Action::PLAY:
        {
          _msgReceived.emplace_back(std::make_pair("play", std::make_pair(entityId, client->GetId())));
        }
        break;
        case Action::MENU:
        {
          _msgReceived.emplace_back(std::make_pair("menu", std::make_pair(entityId, client->GetId())));
        }
        break;
        case Action::KEYBIND:
        {
          _msgReceived.emplace_back(std::make_pair("keyBind", std::make_pair(entityId, client->GetId())));
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
          _msgReceived.emplace_back(std::make_pair("clientDisconnection", std::make_pair(numPlayer, client->GetId())));
        }
        break;
        default:
        {
          std::cout << "Unknown action" << std::endl;
        }
        }
      }

      void handleInputMessage(
          std::shared_ptr<rtype::network::NetworkConnection<NetworkMessages>> client,
          rtype::network::Message<NetworkMessages> &message)
      {
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

            for (std::shared_ptr<NetworkConnection<T>> &connection :
                 deqConnections) {
              if (connection->GetEndpoint() == clientEndpoint) {
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
            }
          }
          WaitForMessage(); });
      }

      void sendAllEntitiesUpdateOrCreateToAllClient(std::shared_ptr<rtype::network::NetworkConnection<T>> clientToIgnore)
      {
        bool transform = false;
        for (std::shared_ptr<entity::IEntity> &entity : _entityManager.getEntities())
        {
          if (entity->getCommunication() == entity::EntityCommunication::CREATE)
          {
            queueOfOutgoingMessages.push_back(std::make_pair(networkMessageFactory.createEntityMsg(entity->getID(), entity->getSceneStatus(), entity->getNumClient()), std::make_pair(entity->getID(), entity->getNumClient())));
            if (entity->getNumClient() != -1)
            {
              for (int i = 0; i < deqConnections.size(); i++)
              {
                if (i == entity->getNumClient())
                {
                  SendMessageToClient(networkMessageFactory.createEntityMsg(entity->getID(), entity->getSceneStatus(), entity->getNumClient()), deqConnections[i]);
                  queueOfAckMessages.push_back(std::make_pair(ServerStatus::WAITING_FOR_CREATE_ENTITY, entity->getID()));
                }
              }
            }
            else
            {
              SendMessageToAllClients(networkMessageFactory.createEntityMsg(entity->getID(), entity->getSceneStatus(), entity->getNumClient()), clientToIgnore);
              int numberOfClient = getNumPlayerConnected();
              for (int i = 0; i < numberOfClient; i++)
              {
                queueOfAckMessages.push_back(std::make_pair(ServerStatus::WAITING_FOR_CREATE_ENTITY, entity->getID()));
              }
            }
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

            if (entity->getNumClient() != -1)
            {
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
              component->setCommunication(component::ComponentCommunication::NONE);
              SendMessageToAllClients(networkMessageFactory.createSpriteMsg(entity->getID(), component->getX(), component->getY(), component->getColor()), clientToIgnore);
            }
            else if (component->getCommunication() == component::ComponentCommunication::UPDATE)
            {
              component->setCommunication(component::ComponentCommunication::NONE);
              SendMessageToAllClients(networkMessageFactory.updateSpriteMsg(entity->getID(), component->getX(), component->getY(), component->getColor()), clientToIgnore);
            }
            else if (component->getCommunication() == component::ComponentCommunication::DELETE)
            {
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
              auto textureKey = getKeyByValue(_stringCom.texturePath, component->getPath());
              if (textureKey)
                SendMessageToAllClients(networkMessageFactory.updateTextureMsg(entity->getID(), *textureKey), clientToIgnore);
              else
                SendMessageToAllClients(networkMessageFactory.updateTextureMsg(entity->getID(), TexturePath::Unknown), clientToIgnore);
            }
            else if (component->getCommunication() == component::ComponentCommunication::DELETE)
            {
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
              component->setCommunication(component::ComponentCommunication::NONE);
              SendMessageToAllClients(networkMessageFactory.createTransformMsg(entity->getID(), component->getPosition().first, component->getPosition().second, component->getScale().first, component->getScale().second, component->getRotation()), clientToIgnore);
            }
            else if (component->getCommunication() == component::ComponentCommunication::UPDATE)
            {
              if (frequencyClock.getElapsedTime() > 0.2)
              {
                component->setCommunication(component::ComponentCommunication::NONE);
                SendMessageToAllClients(networkMessageFactory.updateTransformMsg(entity->getID(), component->getPosition().first, component->getPosition().second, component->getScale().first, component->getScale().second, component->getRotation()), clientToIgnore);
                transform = true;
              }
            }
            else if (component->getCommunication() == component::ComponentCommunication::DELETE)
            {
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

                  queueOfAckMessages.push_back(std::make_pair(ServerStatus::WAITING_FOR_CREATE_INPUT, entity->getID()));
                  queueOfOutgoingMessages.push_back(std::make_pair(networkMessageFactory.createInputMsg(entity->getID(), component->getNumClient()), std::make_pair(entity->getID(), component->getNumClient())));

                  component->setCommunication(component::ComponentCommunication::STANDBY);
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
                  queueOfAckMessages.push_back(std::make_pair(ServerStatus::WAITING_FOR_CREATE_ONCLICK, entity->getID()));
                  queueOfOutgoingMessages.push_back(std::make_pair(networkMessageFactory.createOnClickMsg(entity->getID(), component->getNumClient(), component->getAction()), std::make_pair(entity->getID(), component->getNumClient())));

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
          if (_componentManager.getComponent<component::SoundComponent>(entity->getID()))
          {
            component::SoundComponent *component =
                _componentManager.getComponent<component::SoundComponent>(entity->getID());
            if (component->getCommunication() == component::ComponentCommunication::CREATE)
            {
              component->setCommunication(component::ComponentCommunication::NONE);
              auto soundKey = getKeyByValue(_stringCom.soundPath, component->getPath());
              if (soundKey)
                SendMessageToAllClients(networkMessageFactory.createSoundMsg(entity->getID(), *soundKey, component->getShouldPlay()), clientToIgnore);
              else
                SendMessageToAllClients(networkMessageFactory.createSoundMsg(entity->getID(), SoundPath::Unknown, component->getShouldPlay()), clientToIgnore);
            }
            else if (component->getCommunication() == component::ComponentCommunication::UPDATE)
            {
              component->setCommunication(component::ComponentCommunication::NONE);
              auto soundKey = getKeyByValue(_stringCom.soundPath, component->getPath());
              if (soundKey)
                SendMessageToAllClients(networkMessageFactory.updateSoundMsg(entity->getID(), *soundKey, component->getShouldPlay()), clientToIgnore);
              else
                SendMessageToAllClients(networkMessageFactory.updateSoundMsg(entity->getID(), SoundPath::Unknown, component->getShouldPlay()), clientToIgnore);
            }
            else if (component->getCommunication() == component::ComponentCommunication::DELETE)
            {
              component->setCommunication(component::ComponentCommunication::NONE);
              SendMessageToAllClients(networkMessageFactory.deleteSoundMsg(entity->getID()), clientToIgnore);
            }
          }
          if (_componentManager.getComponent<component::MusicComponent>(entity->getID()))
          {
            component::MusicComponent *component =
                _componentManager.getComponent<component::MusicComponent>(entity->getID());
            if (component->getCommunication() == component::ComponentCommunication::CREATE)
            {
              component->setCommunication(component::ComponentCommunication::NONE);
              auto musicKey = getKeyByValue(_stringCom.soundPath, component->getPath());
              if (musicKey)
                SendMessageToAllClients(networkMessageFactory.createMusicMsg(entity->getID(), *musicKey, component->getShouldPlay()), clientToIgnore);
              else
                SendMessageToAllClients(networkMessageFactory.createMusicMsg(entity->getID(), SoundPath::Unknown, component->getShouldPlay()), clientToIgnore);
            }
            else if (component->getCommunication() == component::ComponentCommunication::UPDATE)
            {
              component->setCommunication(component::ComponentCommunication::NONE);
              auto musicKey = getKeyByValue(_stringCom.soundPath, component->getPath());
              if (musicKey)
                SendMessageToAllClients(networkMessageFactory.updateMusicMsg(entity->getID(), *musicKey, component->getShouldPlay()), clientToIgnore);
              else
                SendMessageToAllClients(networkMessageFactory.updateMusicMsg(entity->getID(), SoundPath::Unknown, component->getShouldPlay()), clientToIgnore);
            }
            else if (component->getCommunication() == component::ComponentCommunication::DELETE)
            {
              component->setCommunication(component::ComponentCommunication::NONE);
              SendMessageToAllClients(networkMessageFactory.deleteMusicMsg(entity->getID()), clientToIgnore);
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
                    entity->getID(), component->getX(), component->getY(), component->getColor()),
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
          if (_componentManager.getComponent<component::SoundComponent>(entity->getID()))
          {
            component::SoundComponent *component =
                _componentManager.getComponent<component::SoundComponent>(entity->getID());
            auto soundKey = getKeyByValue(_stringCom.soundPath, component->getPath());
            if (soundKey)
              SendMessageToClient(networkMessageFactory.createSoundMsg(entity->getID(), *soundKey, component->getShouldPlay()), client);
            else
              SendMessageToClient(networkMessageFactory.createSoundMsg(entity->getID(), SoundPath::Unknown, component->getShouldPlay()), client);
          }
          if (_componentManager.getComponent<component::MusicComponent>(entity->getID()))
          {
            component::MusicComponent *component =
                _componentManager.getComponent<component::MusicComponent>(entity->getID());
            auto musicKey = getKeyByValue(_stringCom.soundPath, component->getPath());
            if (musicKey)
              SendMessageToClient(networkMessageFactory.createMusicMsg(entity->getID(), *musicKey, component->getShouldPlay()), client);
            else
              SendMessageToClient(networkMessageFactory.createMusicMsg(entity->getID(), SoundPath::Unknown, component->getShouldPlay()), client);
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
        return true;
      }

      void Stop()
      {
        asioContext.stop();

        if (contextThread.joinable())
          contextThread.join();
      }

      void SendMessageToClient(const Message<T> &message,
                               std::shared_ptr<NetworkConnection<T>> client)
      {
        if (client && client->IsConnected())
        {
          client->Send(message);
        }
        else
        {
          OnClientDisconnection(client);
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

      int getNumPlayerConnected()
      {
        int numPlayer = 0;
        for (int i = 0; i < 4; i++)
        {
          if (_playerConnected[i].first == true)
            numPlayer++;
        }
        return numPlayer;
      }

      void ServerUpdate(size_t maxMessages = -1, bool needToWait = false)
      {
        if (needToWait == true)
          incomingMessages.wait();
        size_t messageCount = 0;
        std::chrono::milliseconds timeout(100);
        bool ackMessage = true;

        while (messageCount < maxMessages && !incomingMessages.empty())
        {
          auto msg = incomingMessages.popFront();
          rtype::Clock actualClock;

          if (actualClock.getElapsedTime() > 2.0)
          {
            if (!queueOfOutgoingMessages.empty())
            {
              ServerStatus statusToSend;
              for (auto &actualMsg : queueOfOutgoingMessages)
              {
                switch (actualMsg.first.header.id)
                {
                case NetworkMessages::createEntity:
                {
                  statusToSend = ServerStatus::WAITING_FOR_CREATE_ENTITY;
                }
                break;
                case NetworkMessages::createInput:
                {
                  statusToSend = ServerStatus::WAITING_FOR_CREATE_INPUT;
                }
                break;
                case NetworkMessages::createOnClick:
                {
                  statusToSend = ServerStatus::WAITING_FOR_CREATE_ONCLICK;
                }
                break;
                case NetworkMessages::createRectangleShape:
                {
                  statusToSend = ServerStatus::WAITING_FOR_CREATE_RECTANGLE_SHAPE;
                }
                break;
                case NetworkMessages::createText:
                {
                  statusToSend = ServerStatus::WAITING_FOR_CREATE_TEXT;
                }
                break;
                }
                SendMessageToClient(actualMsg.first, deqConnections[actualMsg.second.second]);
                queueOfAckMessages.push_back(std::make_pair(statusToSend, actualMsg.second.first));
              }
            }
          }

          if (queueOfAckMessages.empty() == false)
          {

            OnMessageReceived(msg.remoteConnection, msg.message);
            for (auto &incomingMsg : incomingMessages.getQueue())
            {
              if (incomingMsg.message.header.id != NetworkMessages::acknowledgementMesageToCreateEntity || msg.message.header.id != NetworkMessages::acknowledgementMesageToCreateEntity)
              {
                ackMessage = false;
                break;
              }
            }
            if (ackMessage == false && queueOfAckMessages.size() > 0 && queueOfOutgoingMessages.size() > 0)
            {
              queueOfAckMessages.clear();
              queueOfOutgoingMessages.clear();
            }
          }
          else
          {
            OnMessageReceived(msg.remoteConnection, msg.message);
            actualClock.restart();
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
        if (msgToSend.first == Action::MENU)
          SendMessageToClient(networkMessageFactory.createMenuMsg(), deqConnections[msgToSend.second]);
        else if (msgToSend.first == Action::GAME)
          SendMessageToClient(networkMessageFactory.createGameMsg(), deqConnections[msgToSend.second]);
        else if (msgToSend.first == Action::KEYBIND)
          SendMessageToClient(networkMessageFactory.createKeyBindMsg(), deqConnections[msgToSend.second]);
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
      std::vector<std::pair<ServerStatus, uint32_t>> queueOfAckMessages;
      std::vector<std::pair<rtype::network::Message<NetworkMessages>, std::pair<uint32_t, int>>> queueOfOutgoingMessages;
      rtype::Clock startClock;

      std::vector<std::pair<std::string, std::pair<size_t, size_t>>> _msgReceived;

    private:
      std::vector<std::pair<bool, int>> _playerConnected;
      component::ComponentManager &_componentManager;
      entity::EntityManager &_entityManager;
      rtype::Clock frequencyClock;
    };
  }
}
#endif /* !SERVER_HPP_ */
