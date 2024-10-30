/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ClientSystem
*/

#pragma once

#include <r-type/AClient.hpp>
#include <CoreModule.hpp>
#include <NetworkMessage.hpp>
#include <NetworkMessageFactory.hpp>
#include <NetworkMessagesCommunication.hpp>
#include <r-type/ASystem.hpp>
#include <mutex>
#include <thread>
#include <future>
#include <queue>

namespace rtype
{
  namespace network
  {
    class ClientSystem : virtual public rtype::network::AClient<NetworkMessages>, virtual public ECS_system::ASystem
    {
    public:
      ClientSystem(component::ComponentManager &componentManager,
                   entity::EntityManager &entityManager) : AClient(), ASystem(componentManager, entityManager), _componentManager(componentManager), _entityManager(entityManager), _entityMutex(nullptr)
      {
        Connect("127.0.0.1", 60000);
        startMessageProcessing();
        _sceneStatus = std::make_shared<entity::SceneStatus>(entity::SceneStatus::MENU);
      }

      ~ClientSystem()
      {
        stopMessageProcessing();
      }

      void PingServer()
      {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::ServerPing;
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();

        message << timeNow;

        Send(message);
        std::cout << "Message sent : " << message << std::endl;
      }

      void SendMessageToAllClients()
      {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::MessageAll;

        Send(message);
      }

      void startMessageProcessing();
      void stopMessageProcessing();
      void enqueueMessage(Message<NetworkMessages> msg);

      void handleMessage(rtype::network::Message<NetworkMessages> &msg);

      std::string GetTexturePath(TexturePath texture);

      NetworkMessages getAction(std::string action);

      std::string getStringAction(BindAction action);

      sf::Keyboard::Key getKey(KeyBoard key);

      component::Type getTypedEntity(EntityType type);

      virtual void Disconnect() {}

      void initialize() override {};
      void handleComponents() override {};

      void
      update(float deltaTime,
             std::vector<std::shared_ptr<entity::IEntity>> entities,
             std::vector<std::pair<std::string, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<entity::SceneStatus> &sceneStatus) override;

    protected:
      std::shared_ptr<entity::SceneStatus> _sceneStatus;

    private:
      uint8_t entityID = 0;
      NetworkMessageFactory _networkMessageFactory;
      component::ComponentManager &_componentManager;
      entity::EntityManager &_entityManager;

      std::mutex *_entityMutex;
      std::queue<Message<NetworkMessages>> messageQueue;
      std::mutex queueMutex;                  // Mutex for queue access
      std::condition_variable queueCondition; // Condition variable to notify threads
      bool processingMessages;                // Flag to control threads
      std::vector<std::thread> workerThreads;
    };
  } // namespace network
} // namespace rtype
