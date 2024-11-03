/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ClientSystem
*/

#pragma once

#include <r-type/AClient.hpp>
#include <RtypeEngine.hpp>
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
      /**
       * @class ClientSystem
       * @brief A system that handles client-side operations in the ECS framework.
       *
       * This class inherits from AClient and ASystem, and is responsible for managing
       * client-side components and entities. It also handles the connection to the server
       * and processes incoming messages.
       *
       * @param componentManager Reference to the ComponentManager that handles components.
       * @param entityManager Reference to the EntityManager that handles entities.
       * @param graphic Shared pointer to an IGraphic instance for graphical operations.
       * @param stringCom StringCom instance for communication purposes.
       *
       * @details
       * The constructor initializes the client system by connecting to the server at
       * "localhost" on port 60000 and starts processing messages. It also sets the initial
       * scene status to MENU.
       */
      ClientSystem(component::ComponentManager &componentManager,
                   entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic, std::shared_ptr<IAudio> audio, ECS_system::StringCom stringCom) : AClient(), ASystem(componentManager, entityManager, graphic, audio, stringCom), _componentManager(componentManager), _entityManager(entityManager), _entityMutex(nullptr)
      {
        Connect("127.0.0.1", 60000);
        startMessageProcessing();
        _sceneStatus = std::make_shared<Scene>(Scene::MENU);
      }

      /**
       * @brief Destructor for the ClientSystem class.
       *
       * This destructor ensures that message processing is stopped
       * when an instance of ClientSystem is destroyed.
       */
      ~ClientSystem()
      {
        stopMessageProcessing();
      }

      /**
       * @brief Sends a ping message to the server.
       *
       * This function creates a ping message with the current system time and sends it to the server.
       * It also outputs the message to the standard output.
       */
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

      /**
       * @brief Sends a message to all connected clients.
       *
       * This function creates a message with the header ID set to `NetworkMessages::MessageAll`
       * and sends it to all clients connected to the server.
       */
      void SendMessageToAllClients()
      {
        rtype::network::Message<NetworkMessages> message;
        message.header.id = NetworkMessages::MessageAll;

        Send(message);
      }

      /**
       * @brief Starts the processing of incoming messages for the client system.
       *
       * This function initiates the handling and processing of messages received
       * from the server or other clients. It sets up necessary resources and
       * mechanisms to ensure that messages are processed efficiently and correctly.
       */
      void startMessageProcessing();

      /**
       * @brief Stops the processing of incoming messages.
       *
       * This function halts any ongoing message processing activities, ensuring that
       * no further messages are processed until message processing is explicitly
       * restarted. It is useful in scenarios where message handling needs to be
       * temporarily paused or stopped.
       */
      void stopMessageProcessing();

      /**
       * @brief Enqueues a message to be processed by the client system.
       *
       * This function takes a message of type Message<NetworkMessages> and adds it to the queue
       * for further processing. It ensures that the message is stored and handled appropriately
       * within the client system.
       *
       * @param msg The message to be enqueued, of type Message<NetworkMessages>.
       */
      void enqueueMessage(Message<NetworkMessages> msg);

      /**
       * @brief Sends an acknowledgment message for a specific entity.
       *
       * This function sends an acknowledgment message of the specified type for the given entity ID.
       *
       * @param actualEntityId The ID of the entity for which the acknowledgment message is being sent.
       * @param messageType The type of the acknowledgment message to be sent.
       */
      void sendAckMessage(size_t actualEntityId, NetworkMessages messageType);

      /**
       * @brief Handles incoming network messages.
       *
       * This function processes the given network message and performs
       * appropriate actions based on the message type.
       *
       * @param msg The network message to handle, encapsulated in a
       *            rtype::network::Message object.
       */
      void handleMessage(rtype::network::Message<NetworkMessages> &msg);

      /**
       * @brief Retrieves the file path of a given texture.
       *
       * @param texture The texture for which the file path is to be retrieved.
       * @return std::string The file path of the specified texture.
       */
      std::string GetTexturePath(TexturePath texture);

      /**
       * @brief Disconnects the client from the server.
       *
       * This function is intended to be overridden by derived classes to provide
       * specific disconnection logic. By default, it does nothing.
       */
      virtual void Disconnect() {}

      /**
       * @brief Initializes the client system.
       *
       * This function is called to set up any necessary resources or state
       * for the client system. It overrides the base class implementation.
       */
      void initialize() override {};

      /**
       * @brief Handles the components for the client system.
       *
       * This function is an override of a base class method. It is responsible for
       * managing or processing the components associated with the client system.
       */
      void handleComponents() override {};

      /**
       * @brief Updates the client system.
       *
       * @param deltaTime The time elapsed since the last update.
       * @param entities A vector of shared pointers to entities to be updated.
       * @param msgToSend A reference to a vector of pairs containing actions and their corresponding sizes to be sent.
       * @param msgReceived A reference to a vector of pairs containing strings and their corresponding size pairs of received messages.
       * @param entityMutex A reference to a mutex for synchronizing access to entities.
       * @param sceneStatus A shared pointer to the current scene status.
       */
      void
      update(float deltaTime,
             std::vector<std::shared_ptr<entity::IEntity>> entities,
             std::vector<std::pair<Action, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<Scene> &sceneStatus) override;

    protected:
      /**
       * @brief A shared pointer to a Scene object.
       *
       * This member variable holds a shared pointer to a Scene object,
       * which represents the current status of the scene in the client system.
       * The use of std::shared_ptr ensures that the Scene object is
       * properly managed and deallocated when no longer in use.
       */
      std::shared_ptr<Scene> _sceneStatus;

    private:
      /**
       * @brief The unique identifier for an entity.
       *
       * This variable holds the ID of an entity, which is used to uniquely
       * identify and manage entities within the system.
       */
      uint8_t entityID = 0;

      /**
       * @brief A factory class responsible for creating network messages.
       *
       * The NetworkMessageFactory class provides methods to create and manage
       * different types of network messages used in the client system.
       */
      NetworkMessageFactory _networkMessageFactory;

      /**
       * @brief Reference to the ComponentManager instance.
       *
       * This member variable holds a reference to the ComponentManager, which is responsible
       * for managing all the components within the system. It provides functionalities to
       * add, remove, and access components.
       */
      component::ComponentManager &_componentManager;

      /**
       * @brief Reference to the EntityManager instance.
       *
       * This member variable holds a reference to the EntityManager, which is responsible
       * for managing all entities within the system. It provides functionalities to create,
       * destroy, and manipulate entities.
       */
      entity::EntityManager &_entityManager;

      /**
       * @brief A pointer to a mutex used for synchronizing access to entities.
       */
      std::mutex *_entityMutex;

      /**
       * @brief A queue to store messages of type NetworkMessages.
       *
       * This queue is used to manage and process messages in a FIFO (First In, First Out) order.
       * Each message is encapsulated in a Message object which contains the data and metadata
       * related to the network communication.
       */
      std::queue<Message<NetworkMessages>> messageQueue;

      /**
       * @brief Mutex to protect access to the queue.
       *
       * This mutex is used to ensure that access to the queue is thread-safe.
       * It should be locked before accessing the queue and unlocked after the
       * access is complete to prevent data races and ensure consistency.
       */
      std::mutex queueMutex;

      /**
       * @brief A condition variable for synchronizing access to a shared resource.
       *
       * This condition variable is used to block one or more threads until another
       * thread notifies them that a condition has been met. It is typically used
       * in conjunction with a mutex to protect shared data.
       */
      std::condition_variable queueCondition;

      /**
       * @brief Flag indicating whether the system is currently processing messages.
       */
      bool processingMessages;

      /**
       * @brief A vector to hold worker threads.
       *
       * This member variable is a container that stores multiple std::thread objects.
       * Each thread in this vector represents a worker thread that can be used to
       * perform concurrent tasks.
       */
      std::vector<std::thread> workerThreads;

    };
  } // namespace network
} // namespace rtype
