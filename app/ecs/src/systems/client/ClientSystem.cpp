/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ClientSystem
*/

#include <systems/ClientSystem.hpp>

namespace rtype
{
  namespace network
  {

    /**
     * @brief Sends an acknowledgment message to the network.
     *
     * This function constructs a network message containing an acknowledgment
     * for a specific entity and sends it. The message includes the entity ID
     * and the current timestamp.
     *
     * @param actualEntityId The ID of the entity for which the acknowledgment is being sent.
     * @param messageType The type of the network message to be sent.
     */
    void ClientSystem::sendAckMessage(size_t actualEntityId, NetworkMessages messageType)
    {
      rtype::network::Message<NetworkMessages> message;
      EntityId entityToSend = {actualEntityId};
      message.header.id = messageType;

      std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&entityToSend),
                                       reinterpret_cast<uint8_t *>(&entityToSend) +
                                           sizeof(EntityId));
      message.body.insert(message.body.end(), entityBytes.begin(),
                          entityBytes.end());

      std::chrono::system_clock::time_point timeNow =
          std::chrono::system_clock::now();
      message << timeNow;

      Send(message);
    }

    /**
     * @brief Handles incoming network messages and performs appropriate actions based on the message type.
     *
     * @param msg The network message to handle.
     *
     * This function processes various types of network messages and updates the client state accordingly.
     * It uses a switch statement to determine the type of message and performs actions such as creating,
     * updating, or deleting entities and components, changing scenes, and handling server communication.
     *
     * The supported message types include:
     * - NetworkMessages::ServerAcceptance: Logs server acceptance of connection.
     *
     * - NetworkMessages::ServerPing: Calculates and logs the ping time.
     *
     * - NetworkMessages::ServerMessage: Logs a message from the server with the client ID.
     *
     * - NetworkMessages::ServerDenial: Placeholder for server denial handling.
     *
     * - NetworkMessages::MessageAll: Placeholder for handling messages to all clients.
     *
     * - NetworkMessages::ClientConnection: Placeholder for handling client connection.
     *
     * - NetworkMessages::menu: Creates a menu scene on the client side.
     *
     * - NetworkMessages::game: Creates a game scene on the client side.
     *
     * - NetworkMessages::keyBind: Creates a key binding scene on the client side.
     *
     * - NetworkMessages::createEntity: Creates an entity with the specified ID and scene status.
     *
     * - NetworkMessages::updateEntity: Updates an entity's scene status.
     *
     * - NetworkMessages::deleteEntity: Deletes an entity and removes all its components.
     *
     * - NetworkMessages::createSprite: Creates a sprite component for an entity.
     *
     * - NetworkMessages::createTexture: Creates a texture component for an entity.
     *
     * - NetworkMessages::createTransform: Creates a transform component for an entity.
     *
     * - NetworkMessages::createVelocity: Creates a velocity component for an entity.
     *
     * - NetworkMessages::createParent: Creates a parent component for an entity.
     *
     * - NetworkMessages::createHealth: Creates a health component for an entity.
     *
     * - NetworkMessages::createDamage: Creates a damage component for an entity.
     *
     * - NetworkMessages::createHitbox: Creates a hitbox component for an entity.
     *
     * - NetworkMessages::createInput: Creates an input component for an entity.
     *
     * - NetworkMessages::updateInput: Updates an input component for an entity.
     *
     * - NetworkMessages::createType: Creates a type component for an entity.

     * - NetworkMessages::updateType: Updates a type component for an entity.

     * - NetworkMessages::updateSprite: Updates a sprite component for an entity.

     * - NetworkMessages::updateTransform: Updates a transform component for an entity.

     * - NetworkMessages::updateVelocity: Updates a velocity component for an entity.

     * - NetworkMessages::updateParent: Updates a parent component for an entity.

     * - NetworkMessages::updateHealth: Updates a health component for an entity.
     * - NetworkMessages::updateDamage: Updates a damage component for an entity.
     *
     * - NetworkMessages::updateHitbox: Updates a hitbox component for an entity.
     *
     * - NetworkMessages::createSize: Creates a size component for an entity.
     *
     * - NetworkMessages::updateSize: Updates a size component for an entity.
     *
     * - NetworkMessages::createRectangleShape: Creates a rectangle shape component for an entity.
     *
     * - NetworkMessages::updateRectangleShape: Updates a rectangle shape component for an entity.
     *
     * - NetworkMessages::createOnClick: Creates an on-click component for an entity.
     *
     * - NetworkMessages::createText: Creates a text component for an entity.
     *
     * - NetworkMessages::updateText: Updates a text component for an entity.
     *
     * - NetworkMessages::createSound: Creates a sound component for an entity.
     *
     * - NetworkMessages::updateSound: Updates a sound component for an entity.
     *
     * - NetworkMessages::createMusic: Creates a music component for an entity.
     *
     * - NetworkMessages::updateMusic: Updates a music component for an entity.
     *
     * The function uses std::memcpy to extract data from the message body and update the corresponding
     * components in the entity-component system. It also sends acknowledgment messages for certain actions.
     */
    void ClientSystem::handleMessage(rtype::network::Message<NetworkMessages> &msg)
    {
      std::lock_guard<std::mutex> lock(*_entityMutex);

      switch (msg.header.id)
      {
      case NetworkMessages::ServerPing:
      {
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        std::chrono::system_clock::time_point timeThen;
        msg >> timeThen;
      }
      break;
      case NetworkMessages::ServerMessage:
      {
        uint32_t clientID;
        msg >> clientID;
      }
      break;
      case NetworkMessages::ServerDenial:
      {
      }
      break;
      case NetworkMessages::MessageAll:
      {
      }
      break;
      case NetworkMessages::ClientConnection:
      {
      }
      break;
      case NetworkMessages::menu:
      {
        _sceneStatus = std::make_shared<Scene>(Scene::MENU);
      }
      break;
      case NetworkMessages::game:
      {
        _sceneStatus = std::make_shared<Scene>(Scene::GAME);
      }
      break;
      case NetworkMessages::keyBind:
      {
        _sceneStatus = std::make_shared<Scene>(Scene::KEYBIND);
      }
      break;
      case NetworkMessages::createEntity:
      {
        EntityStruct entityId;
        SceneStatus scene;
        if (msg.body.size() < sizeof(EntityStruct) + sizeof(SceneStatus))
        {
          return;
        }
        std::memcpy(&entityId, msg.body.data(), sizeof(EntityStruct));
        std::memcpy(&scene, msg.body.data() + sizeof(EntityStruct),
                    sizeof(SceneStatus));
        entity::IEntity *entity = _entityManager.createEntity(entityId.id, entityId.numClient);
        entity->setSceneStatus(scene.scene);
        sendAckMessage(entityId.id, NetworkMessages::acknowledgementMesageToCreateEntity);
      }
      break;
      case NetworkMessages::updateEntity:
      {
        EntityStruct entityId;
        SceneStatus scene;
        std::memcpy(&entityId, msg.body.data(), sizeof(EntityStruct));
        std::memcpy(&scene, msg.body.data() + sizeof(EntityStruct),
                    sizeof(SceneStatus));
        entity::IEntity *entity = _entityManager.getEntityByID(entityId.id);
        if (entity == nullptr)
          return;
        entity->setSceneStatus(scene.scene);
      }
      case NetworkMessages::deleteEntity:
      {
        EntityId entity;
        std::memcpy(&entity, msg.body.data(), sizeof(EntityId));
        _componentManager.removeAllComponents(entity.id);
        _entityManager.removeEntity(entity.id);
      }
      break;
      case NetworkMessages::createSprite:
      {
        SpriteComponent sprite;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&sprite, msg.body.data() + sizeof(EntityId),
                    sizeof(SpriteComponent));
        _componentManager
            .addComponent<component::SpriteComponent>(id.id, sprite.x, sprite.y, sprite.color, _graphic);
      }
      break;
      case NetworkMessages::createTexture:
      {
        TextureComponent texture;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&texture, msg.body.data() + sizeof(EntityId),
                    sizeof(TextureComponent));
        if (_stringCom.texturePath.find(texture.texturePath) == _stringCom.texturePath.end())
          _componentManager
              .addComponent<component::TextureComponent>(
                  id.id, _stringCom.texturePath[TexturePath::Unknown], _graphic);
        else
          _componentManager
              .addComponent<component::TextureComponent>(
                  id.id, _stringCom.texturePath[texture.texturePath], _graphic);
      }
      break;
      case NetworkMessages::createTransform:
      {
        TransformComponent transform;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&transform, msg.body.data() + sizeof(EntityId),
                    sizeof(TransformComponent));
        _componentManager
            .addComponent<component::TransformComponent>(
                id.id, std::make_pair(transform.x, transform.y),
                std::make_pair(transform.scaleX, transform.scaleY), transform.rotation);
      }
      break;
      case NetworkMessages::createVelocity:
      {
        VelocityComponent velocity;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&velocity, msg.body.data() + sizeof(EntityId),
                    sizeof(VelocityComponent));
        _componentManager
            .addComponent<component::VelocityComponent>(
                id.id, std::make_pair(velocity.x, velocity.y), std::make_pair(velocity.actualX, velocity.actualY));
      }
      break;
      case NetworkMessages::createParent:
      {
        ParentComponent parent;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&parent, msg.body.data() + sizeof(EntityId),
                    sizeof(ParentComponent));
        _componentManager
            .addComponent<component::ParentComponent>(id.id, parent.parentID);
      }
      break;
      case NetworkMessages::createHealth:
      {
        HealthComponent health;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&health, msg.body.data() + sizeof(EntityId),
                    sizeof(HealthComponent));
        _componentManager
            .addComponent<component::HealthComponent>(id.id, health.health);
      }
      break;
      case NetworkMessages::createDamage:
      {
        DamageComponent damage;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&damage, msg.body.data() + sizeof(EntityId),
                    sizeof(DamageComponent));
        _componentManager
            .addComponent<component::DamageComponent>(id.id, damage.damage);
      }
      break;
      case NetworkMessages::createHitbox:
      {
        HitboxComponent hitbox;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&hitbox, msg.body.data() + sizeof(EntityId),
                    sizeof(HitboxComponent));
        _componentManager
            .addComponent<component::HitBoxComponent>(id.id, hitbox.x, hitbox.y);
      }
      break;
      case NetworkMessages::createInput:
      {
        EntityId id;
        InputComponent input;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&input, msg.body.data() + sizeof(EntityId),
                    sizeof(InputComponent));
        _componentManager.addComponent<component::InputComponent>(id.id, input.numClient);

        sendAckMessage(id.id, NetworkMessages::acknowledgementMesageToCreateInput);
      }
      break;
      case NetworkMessages::updateInput:
      {
        BindKey input;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&input, msg.body.data() + sizeof(EntityId),
                    sizeof(BindKey));
        _componentManager
            .updateComponent<component::InputComponent>(id.id, input.action,
                                                        input.key);
      }
      break;
      case NetworkMessages::createType:
      {
        TypeComponent type;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&type, msg.body.data() + sizeof(EntityId),
                    sizeof(TypeComponent));
        _componentManager
            .addComponent<component::TypeComponent>(id.id, type.type);
      }
      break;
      case NetworkMessages::updateType:
      {
        TypeComponent type;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&type, msg.body.data() + sizeof(EntityId),
                    sizeof(TypeComponent));
        _componentManager
            .updateComponent<component::TypeComponent>(id.id, type.type);
      }
      break;
      case NetworkMessages::updateSprite:
      {
        SpriteComponent sprite;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&sprite, msg.body.data() + sizeof(EntityId),
                    sizeof(SpriteComponent));
        _componentManager
            .updateComponent<component::SpriteComponent>(id.id, sprite.x,
                                                         sprite.y, _graphic);
      }
      break;
      case NetworkMessages::updateTransform:
      {
        TransformComponent transform;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&transform, msg.body.data() + sizeof(EntityId),
                    sizeof(TransformComponent));
        _componentManager
            .updateComponent<component::TransformComponent>(
                id.id, std::make_pair(transform.x, transform.y),
                std::make_pair(transform.scaleX, transform.scaleY), transform.rotation);
      }
      break;
      case NetworkMessages::updateVelocity:
      {
        VelocityComponent velocity;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&velocity, msg.body.data() + sizeof(EntityId),
                    sizeof(VelocityComponent));
        _componentManager
            .updateComponent<component::VelocityComponent>(
                id.id, std::make_pair(velocity.x, velocity.y), std::make_pair(velocity.actualX, velocity.actualY));
      }
      break;
      case NetworkMessages::updateParent:
      {
        ParentComponent parent;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&parent, msg.body.data() + sizeof(EntityId),
                    sizeof(ParentComponent));
        _componentManager
            .updateComponent<component::ParentComponent>(id.id, parent.parentID);
      }
      break;
        break;
      case NetworkMessages::updateHealth:
      {
        HealthComponent health;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&health, msg.body.data() + sizeof(EntityId),
                    sizeof(HealthComponent));
        _componentManager
            .updateComponent<component::HealthComponent>(id.id, health.health);
      }
      break;
      case NetworkMessages::updateDamage:
      {
        DamageComponent damage;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&damage, msg.body.data() + sizeof(EntityId),
                    sizeof(DamageComponent));
        _componentManager
            .updateComponent<component::DamageComponent>(id.id, damage.damage);
      }
      break;
      case NetworkMessages::updateHitbox:
      {
        HitboxComponent hitbox;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&hitbox, msg.body.data() + sizeof(EntityId),
                    sizeof(HitboxComponent));
        _componentManager
            .updateComponent<component::HitBoxComponent>(id.id, hitbox.x,
                                                         hitbox.y);
      }
      break;
      case NetworkMessages::createSize:
      {
        SizeComponent size;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&size, msg.body.data() + sizeof(EntityId),
                    sizeof(SizeComponent));
        _componentManager
            .addComponent<component::SizeComponent>(id.id, std::make_pair(size.x, size.y));
      }
      break;
      case NetworkMessages::updateSize:
      {
        SizeComponent size;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&size, msg.body.data() + sizeof(EntityId),
                    sizeof(SizeComponent));
        _componentManager
            .updateComponent<component::SizeComponent>(id.id, std::make_pair(size.x, size.y));
      }
      break;
      case NetworkMessages::createRectangleShape:
      {
        RectangleShapeComponent rectangleShape;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&rectangleShape, msg.body.data() + sizeof(EntityId),
                    sizeof(RectangleShapeComponent));
        _componentManager
            .addComponent<component::RectangleShapeComponent>(id.id, std::make_pair(rectangleShape.x, rectangleShape.y), std::make_pair(rectangleShape.width, rectangleShape.height), rectangleShape.color, _graphic);
      }
      break;
      case NetworkMessages::updateRectangleShape:
      {
        RectangleShapeComponent rectangleShape;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&rectangleShape, msg.body.data() + sizeof(EntityId),
                    sizeof(RectangleShapeComponent));
        _componentManager
            .updateComponent<component::RectangleShapeComponent>(id.id, std::make_pair(rectangleShape.x, rectangleShape.y), std::make_pair(rectangleShape.width, rectangleShape.height), rectangleShape.color, _graphic);
      }
      break;
      case NetworkMessages::createOnClick:
      {
        EntityId id;
        OnClickComponent onClick;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&onClick, msg.body.data() + sizeof(EntityId),
                    sizeof(OnClickComponent));
        _componentManager
            .addComponent<component::OnClickComponent>(id.id, onClick.action, onClick.numClient);
        sendAckMessage(id.id, NetworkMessages::acknowledgementMesageToCreateOnClick);
      }
      break;
      case NetworkMessages::createText:
      {
        TextComponent text;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&text, msg.body.data() + sizeof(EntityId),
                    sizeof(TextComponent));
        if (_stringCom.textFont.find(text.textFont) == _stringCom.textFont.end() && _stringCom.textString.find(text.textString) == _stringCom.textString.end())
          _componentManager
              .addComponent<component::TextComponent>(
                  id.id, std::make_pair(text.x, text.y), _stringCom.textString[TextString::Unknown], text.size, text.color, _stringCom.textFont[TextFont::Unknown], _graphic);
        else if (_stringCom.textFont.find(text.textFont) == _stringCom.textFont.end())
          _componentManager
              .addComponent<component::TextComponent>(
                  id.id, std::make_pair(text.x, text.y), _stringCom.textString[text.textString], text.size, text.color, _stringCom.textFont[TextFont::Unknown], _graphic);
        else if (_stringCom.textString.find(text.textString) == _stringCom.textString.end())
          _componentManager
              .addComponent<component::TextComponent>(
                  id.id, std::make_pair(text.x, text.y), _stringCom.textString[TextString::Unknown], text.size, text.color, _stringCom.textFont[text.textFont], _graphic);
        else
          _componentManager
              .addComponent<component::TextComponent>(
                  id.id, std::make_pair(text.x, text.y), _stringCom.textString[text.textString], text.size, text.color, _stringCom.textFont[text.textFont], _graphic);
      }
      break;
      case NetworkMessages::updateText:
      {
        TextComponent text;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&text, msg.body.data() + sizeof(EntityId),
                    sizeof(TextComponent));
        if (_stringCom.textString.find(text.textString) == _stringCom.textString.end())
          _componentManager
              .updateComponent<component::TextComponent>(
                  id.id, std::make_pair(text.x, text.y), _stringCom.textString[TextString::Unknown], text.size, text.color, _graphic);
        else
          _componentManager
              .updateComponent<component::TextComponent>(
                  id.id, std::make_pair(text.x, text.y), _stringCom.textString[text.textString], text.size, text.color, _graphic);
      }
      break;
      case NetworkMessages::createSound:
      {
        SoundComponent sound;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&sound, msg.body.data() + sizeof(EntityId),
                    sizeof(SoundComponent));
        if (_stringCom.soundPath.find(sound.soundPath) == _stringCom.soundPath.end())
          _componentManager
              .addComponent<component::SoundComponent>(
                  id.id, _stringCom.soundPath[SoundPath::Unknown], _audio);
        else
          _componentManager
              .addComponent<component::SoundComponent>(
                  id.id, _stringCom.soundPath[sound.soundPath], _audio);
        _componentManager.getComponent<component::SoundComponent>(id.id)->setShouldPlay(sound.play);
      }
      break;
      case NetworkMessages::updateSound:
      {
        SoundComponent sound;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&sound, msg.body.data() + sizeof(EntityId),
                    sizeof(SoundComponent));
        component::SoundComponent *component =
            _componentManager.getComponent<component::SoundComponent>(id.id);
        if (!component)
          return;
        component->setShouldPlay(sound.play);
      }
      break;
      case NetworkMessages::createMusic:
      {
        SoundComponent music;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&music, msg.body.data() + sizeof(EntityId),
                    sizeof(SoundComponent));
        if (_stringCom.soundPath.find(music.soundPath) == _stringCom.soundPath.end())
          _componentManager
              .addComponent<component::MusicComponent>(
                  id.id, _stringCom.soundPath[SoundPath::Unknown], _audio);
        else
          _componentManager
              .addComponent<component::MusicComponent>(
                  id.id, _stringCom.soundPath[music.soundPath], _audio);
        _componentManager.getComponent<component::MusicComponent>(id.id)->setShouldPlay(music.play);
      }
      break;
      case NetworkMessages::updateMusic:
      {
        SoundComponent music;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&music, msg.body.data() + sizeof(EntityId),
                    sizeof(SoundComponent));
        component::MusicComponent *component =
            _componentManager.getComponent<component::MusicComponent>(id.id);
        if (!component)
          return;
        component->setShouldPlay(music.play);
      }
      break;
      }
    }

    /**
     * @brief Updates the client system.
     *
     * This function handles the update logic for the client system, including processing incoming and outgoing messages,
     * and updating the scene status.
     *
     * @param deltaTime The time elapsed since the last update.
     * @param entities A vector of shared pointers to entities.
     * @param msgToSend A reference to a vector of pairs containing actions and entity IDs to be sent.
     * @param msgReceived A reference to a vector of pairs containing received messages.
     * @param entityMutex A reference to a mutex for synchronizing access to entities.
     * @param sceneStatus A shared pointer to the current scene status.
     */
    void ClientSystem::update(float deltaTime,
                              std::vector<std::shared_ptr<entity::IEntity>> entities,
                              std::vector<std::pair<Action, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<Scene> &sceneStatus)
    {
      _entityMutex = &entityMutex;
      std::lock_guard<std::mutex> lock(*_entityMutex);
      if (IsConnected())
      {
        if (!GetIncomingMessages().empty())
        {
          while (!GetIncomingMessages().empty())
          {
            rtype::network::Message<NetworkMessages> msg =
                GetIncomingMessages().popFront().message;
            enqueueMessage(msg);
          }
        }
      }
      while (!msgToSend.empty())
      {
        Action msg = msgToSend.front().first;
        EntityId id = {msgToSend.front().second};
        ActionMsg actionMsg = {msg};
        msgToSend.erase(msgToSend.begin());
        rtype::network::Message<NetworkMessages> message;
        NetworkMessages action = NetworkMessages::action;
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&id),
                                         reinterpret_cast<uint8_t *>(&id) +
                                             sizeof(EntityId));
        std::vector<uint8_t> actionBytes(reinterpret_cast<uint8_t *>(&actionMsg),
                                         reinterpret_cast<uint8_t *>(&actionMsg) +
                                             sizeof(ActionMsg));
        message.body.insert(message.body.end(), entityBytes.begin(),
                            entityBytes.end());
        message.body.insert(message.body.end(), actionBytes.begin(),
                            actionBytes.end());
        if (action != NetworkMessages::none)
        {
          message.header.id = action;
          std::chrono::system_clock::time_point timeNow =
              std::chrono::system_clock::now();
          message << timeNow;
          Send(message);
        }
      }
      sceneStatus = _sceneStatus;
    }

    /**
     * @brief Starts the message processing by creating worker threads.
     *
     * This function sets the `processingMessages` flag to true and spawns a number of worker threads equal to the hardware concurrency of the system. Each worker thread continuously waits for messages to be available in the `messageQueue`. When a message is available, it is processed by calling the `handleMessage` function. The threads will stop processing when the `processingMessages` flag is set to false.
     */
    void ClientSystem::startMessageProcessing()
    {
      processingMessages = true;
      for (int i = 0; i < std::thread::hardware_concurrency(); ++i)
      {
        workerThreads.emplace_back([this]()
                                   {
            while (processingMessages) {
                std::unique_lock<std::mutex> lock(queueMutex);
                queueCondition.wait(lock, [this] { return !messageQueue.empty() || !processingMessages; });
                if (!processingMessages) break;
                auto msg = std::move(messageQueue.front());
                messageQueue.pop();
                lock.unlock();
                handleMessage(msg);
            } });
      }
    }

    /**
     * @brief Stops the message processing by setting the processing flag to false,
     *        notifying all waiting threads, and joining all worker threads.
     *
     * This function first acquires a unique lock on the queue mutex to safely set
     * the processingMessages flag to false. It then notifies all threads that are
     * waiting on the queue condition variable. Finally, it iterates through all
     * worker threads, joins them if they are joinable, and clears the workerThreads
     * vector.
     */
    void ClientSystem::stopMessageProcessing()
    {
      {
        std::unique_lock<std::mutex> lock(queueMutex);
        processingMessages = false;
      }
      queueCondition.notify_all();
      for (auto &thread : workerThreads)
      {
        if (thread.joinable())
        {
          thread.join();
        }
      }
      workerThreads.clear();
    }

    /**
     * @brief Enqueues a network message to the message queue.
     *
     * This function safely enqueues a given network message to the message queue
     * using a mutex to ensure thread safety. After the message is enqueued, it
     * notifies one of the waiting threads.
     *
     * @param msg The network message to be enqueued.
     */
    void ClientSystem::enqueueMessage(Message<NetworkMessages> msg)
    {
      {
        std::lock_guard<std::mutex> lock(queueMutex);
        messageQueue.push(std::move(msg));
      }
      queueCondition.notify_one();
    }

    /**
     * @brief Factory function to create a new ClientSystem.
     *
     * This function creates and returns a new instance of the ClientSystem class.
     *
     * @param componentManager Reference to the ComponentManager.
     * @param entityManager Reference to the EntityManager.
     * @param graphic Shared pointer to an IGraphic instance.
     * @param audio Shared pointer to an IAudio instance.
     * @param stringCom StringCom instance for communication.
     * @return ECS_system::ISystem* Pointer to the newly created ClientSystem.
     */
    EXPORT_API ECS_system::ISystem *createSystem(component::ComponentManager &componentManager,
                                                 entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic, std::shared_ptr<IAudio> audio, ECS_system::StringCom stringCom)
    {
      return new rtype::network::ClientSystem(componentManager, entityManager, graphic, audio, stringCom);
    }
  } // namespace network
} // namespace rtype