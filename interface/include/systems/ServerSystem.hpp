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
// #include <variant>

namespace rtype
{
  namespace network
  {
    template <typename T>
    class ServerSystem : virtual public rtype::network::IServer<NetworkMessages>,
                         virtual public ECS_system::ASystem
    {
    public:
      /**
       * @class ServerSystem
       * @brief Manages server-side operations for the game, including network communication and entity management.
       *
       * @param componentManager Reference to the ComponentManager for managing components.
       * @param entityManager Reference to the EntityManager for managing entities.
       * @param graphic Shared pointer to the IGraphic interface for graphical operations.
       * @param audio Shared pointer to the IAudio interface for audio operations.
       * @param stringCom StringCom object for ECS system communication.
       *
       * The constructor initializes the server system, sets up the ASIO socket for UDP communication on port 60000,
       * and starts the server. It also initializes the player connection status for up to 4 players.
       */
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

      /**
       * @brief Destructor for the ServerSystem class.
       *
       * This destructor ensures that the Stop() method is called when a ServerSystem
       * object is destroyed, performing any necessary cleanup operations.
       */
      ~ServerSystem() { Stop(); };

      /**
       * @brief Initializes the server system.
       *
       * This function sets up the necessary components and configurations
       * required for the server system to operate. It should be called
       * before any other operations are performed on the server system.
       */
      void initialize() {};

      /**
       * @brief Handles the components within the system.
       *
       * This function is responsible for managing and processing
       * the components associated with the server system.
       */
      void handleComponents() {};

      /**
       * @brief Handles the action to be taken when an acknowledgment message is received.
       *
       * This function processes the acknowledgment message by removing the corresponding entry
       * from the queue of acknowledgment messages. If an entry is removed and there are outgoing
       * messages, it also removes the corresponding entry from the queue of outgoing messages.
       *
       * @param receivedEntity The entity ID that received the acknowledgment message.
       * @param messageType The type of the network message that was acknowledged.
       */
      void ackMessageReceivedAction(EntityId receivedEntity, NetworkMessages messageType) {
        std::cout << "Queue size before erase : " << queueOfAckMessages.size() << std::endl;
        std::cout << "QUEUE OF OUTGOING MESSAGES SIZE BEFORE : " << queueOfOutgoingMessages.size() << std::endl;
        size_t originalQueueSize = queueOfAckMessages.size();
        queueOfAckMessages.erase(std::remove_if(queueOfAckMessages.begin(), queueOfAckMessages.end(), [receivedEntity](const std::pair<ServerStatus, uint32_t> &ackMessage) {
          return ackMessage.second == receivedEntity.id;
        }), queueOfAckMessages.end());
        if (queueOfAckMessages.size() != originalQueueSize && queueOfOutgoingMessages.size() > 0) {
          // Remove the element of the queueOfOutgoingMessages if the header.id is equal to the header id in the queueOfAckMessages, and also ensure that the entity id match the one in queueOfAckMessages that was erased

          queueOfOutgoingMessages.erase(std::remove_if(queueOfOutgoingMessages.begin(), queueOfOutgoingMessages.end(),
    [receivedEntity, messageType](const std::pair<rtype::network::Message<NetworkMessages>, std::pair<uint32_t, int>> &outgoingMessage) {
        return outgoingMessage.first.header.id == messageType && outgoingMessage.second.first == receivedEntity.id;
    }), queueOfOutgoingMessages.end());
        }
        std::cout << "QUEUE OF OUTGOING MESSAGES SIZE AFTER : " << queueOfOutgoingMessages.size() << std::endl;
        std::cout << "Queue size after erase : " << queueOfAckMessages.size() << std::endl;
      }

      /**
       * @brief Updates the server system.
       *
       * This function updates the server system by processing messages to send,
       * sending entity updates to all clients, and handling received messages.
       *
       * @param deltaTime The time elapsed since the last update.
       * @param entities A vector of shared pointers to entities in the system.
       * @param msgToSend A reference to a vector of pairs containing actions and their associated entity IDs to be sent.
       * @param msgReceived A reference to a vector of pairs containing received messages and their associated entity IDs.
       * @param entityMutex A reference to a mutex for synchronizing access to entities.
       * @param sceneStatus A shared pointer to the current scene status.
       */
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
          // std::cout << "size of msgReceived : " << _msgReceived.size() << std::endl;
          msgReceived.emplace_back(_msgReceived.back());
          _msgReceived.pop_back();
        }
      }

    protected:
      /**
       * @brief Handles the received message from a client.
       *
       * This method is called whenever a message is received from a client. It processes
       * the message based on its type and performs the corresponding actions.
       *
       * @param client A shared pointer to the network connection of the client that sent the message.
       * @param message The message received from the client.
       *
       * The message types handled are:
       * - NetworkMessages::ClientConnection: Logs the client connection.
       *
       * - NetworkMessages::MessageAll: Sends a message to all clients.
       *
       * - NetworkMessages::ServerPing: Logs a ping from the client and sends the message back to the client.
       *
       * - NetworkMessages::acknowledgementMesageToCreateEntity: Acknowledges the creation of an entity.
       *
       * - NetworkMessages::acknowledgementMesageToCreateInput: Acknowledges the creation of an input.
       *
       * - NetworkMessages::acknowledgementMesageToCreateOnClick: Acknowledges the creation of an onClick event.
       *
       * - Default: Handles other types of input messages.
       *
       */
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
          std::cout << client->GetId() << " : Ping the server" << std::endl;
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

      /**
       * @brief Handles action messages received from a client.
       *
       * This function processes different types of actions sent by a client and
       * stores the corresponding messages in the _msgReceived vector. It also
       * handles client disconnection and updates the player connection status.
       *
       * @param client A shared pointer to the client's network connection.
       * @param action The action performed by the client.
       * @param entityId The ID of the entity associated with the action.
       */
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
          //! Need to see if it can be implemented correctly
          // wait for all the threads to finish before executing the disconnection of the client
          // std::this_thread::sleep_for(std::chrono::milliseconds(100));
          // std::cout << "WAITING FOR DISCONNECTION" << std::endl;
          _msgReceived.emplace_back(std::make_pair("clientDisconnection", std::make_pair(numPlayer, client->GetId())));
          // OnClientDisconnection(client);
          // for (; incomingMessages.queueSize() > 0;) {
          //   incomingMessages.popBack();
          // }
          // client->Disconnect();
          // client.reset();
          // return;
        }
        break;
        default:
        {
          std::cout << "Unknown action" << std::endl;
        }
        }
      }

      /**
       * @brief Handles input messages received from a client.
       *
       * This function processes incoming messages from a client and performs
       * actions based on the message type. It currently supports handling
       * action messages and prints an error for unknown message types.
       *
       * @param client A shared pointer to the client's network connection.
       * @param message The message received from the client.
       */
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

      /**
       * @brief Handles the event when a client connects to the server.
       *
       * This function is called when a client establishes a connection with the server.
       * It sends a ServerAcceptance message to the client to acknowledge the connection.
       *
       * @param client A shared pointer to the client's network connection.
       * @return true if the connection is successfully handled.
       */
      virtual bool OnClientConnection(
          std::shared_ptr<rtype::network::NetworkConnection<NetworkMessages>>
              client)
      {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::ServerAcceptance;
        client->Send(message);

        return true;
      }


      /**
       * @brief Handles the disconnection of a client.
       *
       * This method is called when a client disconnects from the server. It removes the client
       * from the list of active connections if the client is valid.
       *
       * @param client A shared pointer to the NetworkConnection object representing the client.
       */
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

      /**
       * @brief Asynchronously waits for incoming messages from clients.
       *
       * This function sets up an asynchronous receive operation on the socket to
       * wait for incoming messages from clients. When a message is received, it
       * checks if the client endpoint is using the IPv4 protocol. If the endpoint
       * is valid and no error occurred, it processes the connection request.
       *
       * If the client is already connected, it logs a message and returns. Otherwise,
       * it creates a new socket and connection object for the client, and if the
       * connection is approved, it adds the connection to the list of connections,
       * establishes the client connection, and sends all entities to the client.
       *
       * If an error occurs during the receive operation, it logs the error message.
       *
       * The function then recursively calls itself to continue waiting for messages.
       */
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

      /**
       * @brief Sends update or create messages for all entities to all clients, except for the specified client to ignore.
       *
       * This function iterates through all entities managed by the entity manager and sends appropriate messages to clients
       * based on the entity's communication status (CREATE, UPDATE, DELETE). It also handles the communication status of
       * various components associated with each entity.
       *
       * @param clientToIgnore A shared pointer to the network connection of the client to ignore when sending messages.
       */
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
                if (i == entity->getNumClient()) {
                  SendMessageToClient(networkMessageFactory.createEntityMsg(entity->getID(), entity->getSceneStatus(), entity->getNumClient()), deqConnections[i]);
                  queueOfAckMessages.push_back(std::make_pair(ServerStatus::WAITING_FOR_CREATE_ENTITY, entity->getID()));
                }
              }
            }
            else {
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
            // queueOfAckMessages.push_back(ServerStatus::WAITING_FOR_MESSAGE);

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
              auto textureKey= getKeyByValue(_stringCom.texturePath, component->getPath());
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
                  std::cout << "ON CREATE" << std::endl;

                  queueOfAckMessages.push_back(std::make_pair(ServerStatus::WAITING_FOR_CREATE_INPUT, entity->getID()));
                  queueOfOutgoingMessages.push_back(std::make_pair(networkMessageFactory.createInputMsg(entity->getID(), component->getNumClient()), std::make_pair(entity->getID(), component->getNumClient())));

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
              // queueOfAckMessages.push_back(ServerStatus::WAITING_FOR_MESSAGE);
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
              // queueOfAckMessages.push_back(std::make_pair(ServerStatus::WAITING_FOR_CREATE_RECTANGLE_SHAPE, entity->getID()));
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
              // queueOfAckMessages.push_back(std::make_pair(ServerStatus::WAITING_FOR_CREATE_TEXT, entity->getID()));
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

      /**
       * @brief Sends all entities and their components to a specified client.
       *
       * This function iterates through all entities managed by the entity manager and sends their
       * relevant component data to the specified client. It checks if the client is connected before
       * proceeding with the data transmission. For each entity, it sends messages for various components
       * such as Sprite, Texture, Text, Transform, Velocity, Health, Damage, HitBox, Parent, Input, Type,
       * AI, Size, RectangleShape, OnClick, Sound, and Music components.
       *
       * @tparam T The type of the network connection.
       * @param client A shared pointer to the network connection of the client.
       * @param numClient The client number to which the entities should be sent.
       */
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

      /**
       * @brief Starts the server and initializes the context thread.
       *
       * This function attempts to start the server by waiting for a message and
       * then running the ASIO context in a separate thread. If an exception of
       * type rtype::RtypeException is thrown, it catches the exception, logs the
       * error message, and returns false. If the server starts successfully, it
       * prints a confirmation message and returns true.
       *
       * @return true if the server starts successfully, false otherwise.
       */
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

      /**
       * @brief Stops the server by stopping the ASIO context and joining the context thread.
       *
       * This function stops the ASIO context, which effectively stops all asynchronous operations.
       * If the context thread is joinable, it joins the thread to ensure proper cleanup.
       * Finally, it prints a message indicating that the server has stopped.
       */
      void Stop()
      {
        asioContext.stop();

        if (contextThread.joinable())
          contextThread.join();
        std::cout << "Server stopped !" << std::endl;
      }

      /**
       * @brief Sends a message to a specific client.
       *
       * This function attempts to send a given message to a specified client.
       * If the client is connected, the message is sent. If the client is not
       * connected, the OnClientDisconnection function is called.
       *
       * @tparam T The type of the message.
       * @param message The message to be sent to the client.
       * @param client A shared pointer to the network connection of the client.
       */
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

      /**
       * @brief Sends a message to all connected clients except the specified client to ignore.
       *
       * This function iterates through all the connections in the deque and sends the provided
       * message to each connected client, except for the client specified to be ignored. If a
       * client is found to be disconnected, it triggers the disconnection handler and marks
       * the presence of an invalid client. After processing all clients, it removes any
       * invalid (disconnected) clients from the deque.
       *
       * @tparam T The type of the message.
       * @param message The message to be sent to all clients.
       * @param clientToIgnore A shared pointer to the client that should be ignored while sending the message. Default is nullptr.
       */
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

      /**
       * @brief Get the number of players currently connected.
       *
       * This function iterates through the _playerConnected array and counts how many players are currently connected.
       *
       * @return int The number of players connected.
       */
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

      /**
       * @brief Updates the server by processing incoming messages and handling acknowledgements.
       *
       * @param maxMessages The maximum number of messages to process in one update. Default is -1 (process all messages).
       * @param needToWait If true, the function will wait for incoming messages before proceeding.
       *
       * This function processes incoming messages from clients, handles timeouts, and manages acknowledgement messages.
       * It performs the following tasks:
       * - Waits for incoming messages if needToWait is true.
       *
       * - Processes up to maxMessages from the incoming message queue.
       *
       * - Checks for timeouts and resends messages if necessary.
       *
       * - Handles acknowledgement messages and clears queues if acknowledgements are not received in time.
       *
       * - Calls OnMessageReceived for each processed message.
       *
       */
      void ServerUpdate(size_t maxMessages = -1, bool needToWait = false)
      {
        if (needToWait == true)
          incomingMessages.wait();
        size_t messageCount = 0;
        // std::chrono::milliseconds timeout(100);
        std::chrono::milliseconds timeout(100);
        bool ackMessage = true;

        while (messageCount < maxMessages && !incomingMessages.empty())
        {
          // std::cout << "size of incoming messages: " << incomingMessages.queueSize() << std::endl;
          auto msg = incomingMessages.popFront();
          rtype::Clock actualClock;

          // auto originalQueueSize = queueOfAckMessages.size();

          //check if threre is a message.header.id not equals to ack in all the incomingMessages, and clear the data in the queueOfAckMessages and in the queueOfOutgoingMessages
          // go through all the incoming messages

          if (actualClock.getElapsedTime() > 2.0)
          {
            std::cout << "TIMEOUT BAH OUI !!!!!!" << std::endl;
            if (!queueOfOutgoingMessages.empty())
            {
              ServerStatus statusToSend;
              for (auto &actualMsg : queueOfOutgoingMessages)
              {
                switch (actualMsg.first.header.id) {
                  case NetworkMessages::createEntity: {
                    statusToSend = ServerStatus::WAITING_FOR_CREATE_ENTITY;
                  } break;
                  case NetworkMessages::createInput: {
                    statusToSend = ServerStatus::WAITING_FOR_CREATE_INPUT;
                  } break;
                  case NetworkMessages::createOnClick: {
                    statusToSend = ServerStatus::WAITING_FOR_CREATE_ONCLICK;
                  } break;
                  case NetworkMessages::createRectangleShape: {
                    statusToSend = ServerStatus::WAITING_FOR_CREATE_RECTANGLE_SHAPE;
                  } break;
                  case NetworkMessages::createText: {
                    statusToSend = ServerStatus::WAITING_FOR_CREATE_TEXT;
                  } break;
                }
                SendMessageToClient(actualMsg.first, deqConnections[actualMsg.second.second]);
                queueOfAckMessages.push_back(std::make_pair(statusToSend, actualMsg.second.first));
              }
            }
          }

          if (queueOfAckMessages.empty() == false) {
            // print the chrono time value
            // auto now = std::chrono::steady_clock::now();
            // std::cout << "Time elapsed: " << std::chrono::duration<double>(now - start).count() << "s" << std::endl;
            // std::chrono::milliseconds secondsValue = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
            // std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
            // check a timer to see if no ack message is received, in this case we resend the message

            // if (secondsValue > timeout) {
            //   std::cout << "TIMEOUT - Resend" << std::endl;
              // if (!queueOfOutgoingMessages.empty()) {
                // for (auto &toto : queueOfOutgoingMessages) {
                  // SendMessageToClient(toto.first, deqConnections[toto.second.second]);
                  // queueOfAckMessages.push_back(std::make_pair(ServerStatus::WAITING_FOR_CREATE_ENTITY, toto.second.first));
                // }
              // }
            //   start = std::chrono::steady_clock::now();
            //   return;
            // }

            std::cout << "Ack message" << std::endl;
            OnMessageReceived(msg.remoteConnection, msg.message);
            for (auto &incomingMsg : incomingMessages.getQueue())
            {
              if (incomingMsg.message.header.id != NetworkMessages::acknowledgementMesageToCreateEntity || msg.message.header.id != NetworkMessages::acknowledgementMesageToCreateEntity)
              {
                std::cout << "ACK NOT FOUND WHILE THE QUEUE IS NOT EMPTY" << std::endl;
                ackMessage = false;
                break;
              }
              std::cout << "AFTER THE IF THAT CHECKS IF THE MESSAGE IS AN ACK" << std::endl;
            }
            if (ackMessage == false && queueOfAckMessages.size() > 0 && queueOfOutgoingMessages.size() > 0)
            {
              std::cout << "CLEARING THE QUEUES" << std::endl;
              // for (auto &toto : queueOfOutgoingMessages) {
              //   SendMessageToClient(toto.first, deqConnections[toto.second.second]);
              //   queueOfAckMessages.push_back(std::make_pair(ServerStatus::WAITING_FOR_CREATE_ENTITY, toto.second.first));
              // }
              queueOfAckMessages.clear();
              queueOfOutgoingMessages.clear();
              // incomingMessages.clear();
              // return;
            }
            // if (queueOfAckMessages.size() != queueOfOutgoingMessages.size()) {
            //   EntityId actualEntityId;
            //   std::memcpy(&actualEntityId, msg.message.body.data(), sizeof(EntityId));
            //   queueOfAckMessages.push_back(std::make_pair(ServerStatus::WAITING_FOR_CREATE_ENTITY, actualEntityId.id));
            // }
          } else {
            std::cout << "No more ack message" << std::endl;
            OnMessageReceived(msg.remoteConnection, msg.message);
            actualClock.restart();
          }
          messageCount++;
        }
      }

      /**
       * @brief This method is called when a client has been successfully validated.
       *
       * @param client A shared pointer to the validated NetworkConnection object.
       */
      virtual void OnClientValidated(std::shared_ptr<NetworkConnection<T>> client)
      {
      }

      /**
       * @brief Retrieves the key associated with a given value in an unordered map.
       *
       * This function searches through the provided unordered map to find the first key
       * that corresponds to the specified value. If such a key is found, it is returned
       * wrapped in a std::optional. If no matching value is found, std::nullopt is returned.
       *
       * @tparam KeyType The type of the keys in the unordered map.
       * @tparam ValueType The type of the values in the unordered map.
       * @param map The unordered map to search through.
       * @param value The value to search for in the map.
       * @return std::optional<KeyType> The key associated with the specified value, or std::nullopt if no such key exists.
       */
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

      /**
       * @brief Handles the message to send based on the action type.
       *
       * This function processes the message to send by checking the action type
       * and sending the appropriate message to the client.
       *
       * @param msgToSend A pair containing the action type and the index of the connection.
       *                  - Action::MENU: Sends a menu message to the client.
       *
       *                  - Action::GAME: Sends a game message to the client.
       *
       *                  - Action::KEYBIND: Sends a keybind message to the client.
       */
      void handleMsgToSend(std::pair<Action, size_t> msgToSend)
      {
        std::cout << "Handling message to send" << std::endl;
        if (msgToSend.first == Action::MENU)
          SendMessageToClient(networkMessageFactory.createMenuMsg(), deqConnections[msgToSend.second]);
        else if (msgToSend.first == Action::GAME)
          SendMessageToClient(networkMessageFactory.createGameMsg(), deqConnections[msgToSend.second]);
        else if (msgToSend.first == Action::KEYBIND)
          SendMessageToClient(networkMessageFactory.createKeyBindMsg(), deqConnections[msgToSend.second]);
      }

      /**
       * @brief A queue that holds incoming messages for the server.
       *
       * This queue stores messages that have been received by the server but not yet processed.
       * The messages are of type `rtype::network::OwnedMessage<T>`, where `T` is the type of the message payload.
       */
      rtype::network::ServerQueue<rtype::network::OwnedMessage<T>> incomingMessages;

      /**
       * @brief A deque that holds shared pointers to NetworkConnection objects.
       *
       * This deque is used to manage a collection of network connections. Each
       * connection is wrapped in a std::shared_ptr to ensure proper memory
       * management and to allow shared ownership of the connections.
       *
       * @tparam T The type of the data that the NetworkConnection handles.
       */
      std::deque<std::shared_ptr<NetworkConnection<T>>> deqConnections;

      /**
       * @brief The io_context class provides core I/O functionality for asynchronous operations.
       *
       * This object is used to initiate and manage asynchronous operations. It is the main
       * entry point for all I/O operations in the Boost.Asio library. The io_context object
       * runs the event loop that dispatches handlers for asynchronous operations.
       *
       * @see https://www.boost.org/doc/libs/1_76_0/doc/html/boost_asio/reference/io_context.html
       */
      asio::io_context asioContext;

      /**
       * @brief Thread object to manage concurrent execution.
       *
       * This member variable represents a thread that can be used to run a function
       * concurrently with other threads. It is part of the C++ Standard Library's
       * threading support and allows for the creation and management of threads.
       */
      std::thread contextThread;

      /**
       * @brief A socket class for sending and receiving datagrams using the UDP protocol.
       *
       * This class provides the necessary functionality to create a UDP socket,
       * which can be used for network communication. It is part of the ASIO library,
       * which is a cross-platform C++ library for network and low-level I/O programming.
       *
       * @see https://think-async.com/Asio/
       */
      asio::ip::udp::socket asioSocket;

      /**
       * @brief Represents an endpoint for a UDP connection.
       *
       * This object holds the address and port number of a remote client
       * in a UDP communication. It is used to specify the destination
       * or source of a UDP packet.
       */
      asio::ip::udp::endpoint clientEndpoint;

      /**
       * @brief A factory class responsible for creating network messages.
       */
      NetworkMessageFactory networkMessageFactory;

      /**
       * @brief Buffer to store incoming messages.
       *
       * This array is used to temporarily hold incoming messages with a maximum size of 1024 characters.
       */
      std::array<char, 1024> bufferOfIncomingMessages;

      /**
       * @brief Holds the current actual ID value.
       */
      uint32_t actualId = 0;

      /**
       * @brief A vector that holds pairs of ServerStatus and uint32_t.
       *
       * This vector is used to store a queue of acknowledgment messages.
       * Each element in the vector is a pair, where the first element is
       * of type ServerStatus representing the status of the server, and
       * the second element is a uint32_t representing an associated value
       * (e.g., a message ID or timestamp).
       */
      std::vector<std::pair<ServerStatus, uint32_t>> queueOfAckMessages;

      /**
       * @brief A queue of outgoing messages to be sent over the network.
       *
       * This vector holds pairs where each pair consists of:
       * - A message of type `rtype::network::Message<NetworkMessages>`.
       * - A nested pair containing:
       *   - A `uint32_t` representing the recipient's ID.
       *   - An `int` representing additional message metadata or status.
       */
      std::vector<std::pair<rtype::network::Message<NetworkMessages>, std::pair<uint32_t, int>>> queueOfOutgoingMessages;

      /**
       * @brief A clock object used to track the start time.
       *
       * This clock is part of the rtype namespace and is used to record the
       * starting time of an event or process. It can be used to measure elapsed
       * time or to synchronize events within the system.
       */
      rtype::Clock startClock;


      /**
       * @brief A vector that stores messages received.
       *
       * Each element in the vector is a pair where:
       * - The first element is a string representing the message.
       * - The second element is a pair of size_t values representing additional data associated with the message.
       */
      std::vector<std::pair<std::string, std::pair<size_t, size_t>>> _msgReceived;

    private:
      /**
       * @brief A vector that holds pairs indicating player connection status.
       *
       * Each pair consists of:
       * - A boolean value representing whether a player is connected (true) or not (false).
       *
       * - An integer representing the player's ID or some other identifier.
       *
       */
      std::vector<std::pair<bool, int>> _playerConnected;

      /**
       * @brief Reference to the ComponentManager instance.
       *
       * This member variable holds a reference to the ComponentManager, which is responsible
       * for managing all the components in the system. It provides functionalities to add,
       * remove, and access components associated with entities.
       */
      component::ComponentManager &_componentManager;

      /**
       * @brief Reference to the EntityManager instance.
       *
       * This member variable holds a reference to the EntityManager, which is responsible
       * for managing all the entities within the system. It provides functionalities to
       * create, destroy, and manipulate entities.
       */
      entity::EntityManager &_entityManager;

      /**
       * @brief A clock object used to measure the frequency of events.
       *
       * This clock can be used to track the time intervals between events
       * and ensure that they occur at the desired frequency.
       */
      rtype::Clock frequencyClock;
    };
  } // namespace network
} // namespace rtype

#endif /* !SERVER_HPP_ */
