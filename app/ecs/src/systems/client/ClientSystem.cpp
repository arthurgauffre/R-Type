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

    void ClientSystem::sendAckMessage()
    {
      rtype::network::Message<NetworkMessages> message;
      message.header.id = NetworkMessages::acknowledgementMesage;
      Send(message);
    }


    void ClientSystem::handleMessage(rtype::network::Message<NetworkMessages> &msg)
    {
      std::lock_guard<std::mutex> lock(*_entityMutex);

      switch (msg.header.id)
      {
      case NetworkMessages::ServerAcceptance:
      {
        std::cout << "Server Accepted Connection" << std::endl;
      }
      break;

      case NetworkMessages::ServerPing:
      {
        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();
        std::chrono::system_clock::time_point timeThen;
        msg >> timeThen;
        std::cout << "Ping: "
                  << std::chrono::duration<double>(timeNow - timeThen).count()
                  << std::endl;
      }
      break;
      case NetworkMessages::ServerMessage:
      {
        uint32_t clientID;
        msg >> clientID;
        std::cout << "Hello from [" << clientID << "]" << std::endl;
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
        std::cout << "Menu CREATED IN ON THE CLIENT SIDE" << std::endl;
        _sceneStatus = std::make_shared<Scene>(Scene::MENU);
        sendAckMessage();
      }
      break;
      case NetworkMessages::game:
      {
        _sceneStatus = std::make_shared<Scene>(Scene::GAME);
      }
      case NetworkMessages::createEntity:
      {
        // std::cout << "Entity created" << std::endl;
        EntityStruct entityId;
        SceneStatus scene;
        if (msg.body.size() < sizeof(EntityStruct) + sizeof(SceneStatus))
          return;
        std::memcpy(&entityId, msg.body.data(), sizeof(EntityStruct));
        if (_entityManager.getEntities().size() + 100 < entityId.id)
          return;
        std::memcpy(&scene, msg.body.data() + sizeof(EntityStruct),
                    sizeof(SceneStatus));
        entity::IEntity *entity = _entityManager.createEntity(entityId.id, entityId.numClient);
        entity->setSceneStatus(scene.scene);
        // Send acknowledgement message
        sendAckMessage();
        // std::cout << "Create component ack message sent" << std::endl;
      }
      break;
      case NetworkMessages::updateEntity:
      {
        // std::cout << "Entity updated" << std::endl;
        EntityStruct entityId;
        SceneStatus scene;
        std::memcpy(&entityId, msg.body.data(), sizeof(EntityStruct));
        std::memcpy(&scene, msg.body.data() + sizeof(EntityStruct),
                    sizeof(SceneStatus));
        // std::cout << "Entity id: " << entity.id << std::endl;
        entity::IEntity *entity = _entityManager.getEntityByID(entityId.id);
        if (entity == nullptr)
          return;
        entity->setSceneStatus(scene.scene);
        // Send acknowledgement message
        // rtype::network::Message<NetworkMessages> message;
        // message.header.id = NetworkMessages::acknowledgementMesage;
        // Send(message);
        // std::cout << "Update component ack message sent" << std::endl;
      }
      case NetworkMessages::deleteEntity:
      {
        // std::cout << "Entity destroyed" << std::endl;
        EntityId entity;
        std::memcpy(&entity, msg.body.data(), sizeof(EntityId));
        // std::cout << "Entity id: " << entity.id << std::endl;
        _componentManager.removeAllComponents(entity.id);
        _entityManager.removeEntity(entity.id);
        sendAckMessage();
      }
      break;
      case NetworkMessages::createSprite:
      {
        // std::cout << "Sprite component created" << std::endl;
        SpriteComponent sprite;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&sprite, msg.body.data() + sizeof(EntityId),
                    sizeof(SpriteComponent));
        // std::cout << "Sprite: " << sprite.x << " " << sprite.y << std::endl;
        _componentManager
            .addComponent<component::SpriteComponent>(id.id, sprite.x, sprite.y, _graphic);
      }
      break;
      case NetworkMessages::createTexture:
      {
        // std::cout << "Texture component created" << std::endl;
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
        // std::cout << "Transform component created" << std::endl;
        TransformComponent transform;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&transform, msg.body.data() + sizeof(EntityId),
                    sizeof(TransformComponent));
        // std::cout << "Transform: " << transform.x << " " << transform.y << " "
        //           << transform.scaleX << " " << transform.scaleY << " " << transform.rotation << std::endl;
        // std::cout << "transform with id " << id.id << std::endl;
        _componentManager
            .addComponent<component::TransformComponent>(
                id.id, std::make_pair(transform.x, transform.y),
                std::make_pair(transform.scaleX, transform.scaleY), transform.rotation);
      }
      break;
      case NetworkMessages::createVelocity:
      {
        // std::cout << "Velocity component created" << std::endl;
        VelocityComponent velocity;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&velocity, msg.body.data() + sizeof(EntityId),
                    sizeof(VelocityComponent));
        // std::cout << "Velocity: " << velocity.x << " " << velocity.y << std::endl;
        _componentManager
            .addComponent<component::VelocityComponent>(
                id.id, std::make_pair(velocity.x, velocity.y), std::make_pair(velocity.actualX, velocity.actualY));
      }
      break;
      case NetworkMessages::createParent:
      {
        // std::cout << "Parent component created" << std::endl;
        ParentComponent parent;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&parent, msg.body.data() + sizeof(EntityId),
                    sizeof(ParentComponent));
        // std::cout << "Parent: " << parent.parentID << std::endl;
        _componentManager
            .addComponent<component::ParentComponent>(id.id, parent.parentID);
      }
      break;
      case NetworkMessages::createHealth:
      {
        // std::cout << "Health component created" << std::endl;
        HealthComponent health;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&health, msg.body.data() + sizeof(EntityId),
                    sizeof(HealthComponent));
        // std::cout << "Health: " << health.health << std::endl;
        _componentManager
            .addComponent<component::HealthComponent>(id.id, health.health);
      }
      break;
      case NetworkMessages::createDamage:
      {
        // std::cout << "Damage component created" << std::endl;
        DamageComponent damage;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&damage, msg.body.data() + sizeof(EntityId),
                    sizeof(DamageComponent));
        // std::cout << "Damage: " << damage.damage << std::endl;
        _componentManager
            .addComponent<component::DamageComponent>(id.id, damage.damage);
      }
      break;
      case NetworkMessages::createHitbox:
      {
        // std::cout << "Hitbox component created" << std::endl;
        HitboxComponent hitbox;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&hitbox, msg.body.data() + sizeof(EntityId),
                    sizeof(HitboxComponent));
        // std::cout << "Hitbox: " << hitbox.x << " " << hitbox.y << std::endl;
        _componentManager
            .addComponent<component::HitBoxComponent>(id.id, hitbox.x, hitbox.y);
      }
      break;
      case NetworkMessages::createInput:
      {
        std::cout << "Input component created" << std::endl;
        EntityId id;
        InputComponent input;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        // _componentManager.addComponent<component::InputComponent>(id.id);
        std::memcpy(&input, msg.body.data() + sizeof(EntityId),
                    sizeof(InputComponent));
        _componentManager.addComponent<component::InputComponent>(id.id, input.numClient);

        sendAckMessage();
        std::cout << "Input component ack message sent" << std::endl;
      }
      break;
      case NetworkMessages::updateInput:
      {
        std::cout << "Input component updated" << std::endl;
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
        // std::cout << "Type component created" << std::endl;
        TypeComponent type;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&type, msg.body.data() + sizeof(EntityId),
                    sizeof(TypeComponent));
        _componentManager
            .addComponent<component::TypeComponent>(id.id, type.type);
        // Send acknowledgement message
        sendAckMessage();
      }
      break;
      case NetworkMessages::updateType:
      {
        // std::cout << "Type component updated" << std::endl;
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
        // std::cout << "Sprite component updated" << std::endl;
        SpriteComponent sprite;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&sprite, msg.body.data() + sizeof(EntityId),
                    sizeof(SpriteComponent));
        // std::cout << "Sprite: " << sprite.x << " " << sprite.y << std::endl;
        _componentManager
            .updateComponent<component::SpriteComponent>(id.id, sprite.x,
                                                         sprite.y, _graphic);
      }
      break;
      case NetworkMessages::updateTransform:
      {
        // std::cout << "Transform component updated" << std::endl;
        TransformComponent transform;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&transform, msg.body.data() + sizeof(EntityId),
                    sizeof(TransformComponent));
        // std::cout << "Transform: " << transform.x << " " << transform.y << " "
        //           << transform.scaleX << " " << transform.scaleY << std::endl;
        _componentManager
            .updateComponent<component::TransformComponent>(
                id.id, std::make_pair(transform.x, transform.y),
                std::make_pair(transform.scaleX, transform.scaleY), transform.rotation);
      }
      break;
      case NetworkMessages::updateVelocity:
      {
        // std::cout << "Velocity component updated" << std::endl;
        VelocityComponent velocity;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&velocity, msg.body.data() + sizeof(EntityId),
                    sizeof(VelocityComponent));
        // std::cout << "Velocity: " << velocity.x << " " << velocity.y << " " << velocity.actualX << " " << velocity.actualY << std::endl;
        _componentManager
            .updateComponent<component::VelocityComponent>(
                id.id, std::make_pair(velocity.x, velocity.y), std::make_pair(velocity.actualX, velocity.actualY));
      }
      break;
      case NetworkMessages::updateParent:
      {
        // std::cout << "Parent component updated" << std::endl;
        ParentComponent parent;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&parent, msg.body.data() + sizeof(EntityId),
                    sizeof(ParentComponent));
        // std::cout << "Parent: " << parent.parentID << std::endl;
        _componentManager
            .updateComponent<component::ParentComponent>(id.id, parent.parentID);
      }
      break;
        break;
      case NetworkMessages::updateHealth:
      {
        // std::cout << "Health component updated" << std::endl;
        HealthComponent health;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&health, msg.body.data() + sizeof(EntityId),
                    sizeof(HealthComponent));
        // std::cout << "Health: " << health.health << std::endl;
        _componentManager
            .updateComponent<component::HealthComponent>(id.id, health.health);
      }
      break;
      case NetworkMessages::updateDamage:
      {
        // std::cout << "Damage component updated" << std::endl;
        DamageComponent damage;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&damage, msg.body.data() + sizeof(EntityId),
                    sizeof(DamageComponent));
        // std::cout << "Damage: " << damage.damage << std::endl;
        _componentManager
            .updateComponent<component::DamageComponent>(id.id, damage.damage);
      }
      break;
      case NetworkMessages::updateHitbox:
      {
        // std::cout << "Hitbox component updated" << std::endl;
        HitboxComponent hitbox;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&hitbox, msg.body.data() + sizeof(EntityId),
                    sizeof(HitboxComponent));
        // std::cout << "Hitbox: " << hitbox.x << " " << hitbox.y << std::endl;
        _componentManager
            .updateComponent<component::HitBoxComponent>(id.id, hitbox.x,
                                                         hitbox.y);
      }
      break;
      case NetworkMessages::createSize:
      {
        // std::cout << "Size component created" << std::endl;
        SizeComponent size;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&size, msg.body.data() + sizeof(EntityId),
                    sizeof(SizeComponent));
        // std::cout << "Size: " << size.x << " " << size.y << std::endl;
        _componentManager
            .addComponent<component::SizeComponent>(id.id, std::make_pair(size.x, size.y));
      }
      break;
      case NetworkMessages::updateSize:
      {
        // std::cout << "Size component updated" << std::endl;
        SizeComponent size;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&size, msg.body.data() + sizeof(EntityId),
                    sizeof(SizeComponent));
        // std::cout << "Size: " << size.x << " " << size.y << std::endl;
        _componentManager
            .updateComponent<component::SizeComponent>(id.id, std::make_pair(size.x, size.y));
      }
      break;
      case NetworkMessages::createRectangleShape:
      {
        // std::cout << "RectangleShape component created" << std::endl;
        RectangleShapeComponent rectangleShape;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&rectangleShape, msg.body.data() + sizeof(EntityId),
                    sizeof(RectangleShapeComponent));
        // std::cout << "rectangle with id " << id.id << std::endl;
        // std::cout << "RectangleShape: " << rectangleShape.x << " " << rectangleShape.y << " " << rectangleShape.width << " " << rectangleShape.height << std::endl;
        _componentManager
            .addComponent<component::RectangleShapeComponent>(id.id, std::make_pair(rectangleShape.x, rectangleShape.y), std::make_pair(rectangleShape.width, rectangleShape.height), rectangleShape.color, _graphic);
        sendAckMessage();
      }
      break;
      case NetworkMessages::updateRectangleShape:
      {
        // std::cout << "RectangleShape component updated" << std::endl;
        RectangleShapeComponent rectangleShape;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&rectangleShape, msg.body.data() + sizeof(EntityId),
                    sizeof(RectangleShapeComponent));
        // std::cout << "RectangleShape: " << rectangleShape.x << " " << rectangleShape.y << " " << rectangleShape.width << " " << rectangleShape.height << std::endl;
        _componentManager
            .updateComponent<component::RectangleShapeComponent>(id.id, std::make_pair(rectangleShape.x, rectangleShape.y), std::make_pair(rectangleShape.width, rectangleShape.height), rectangleShape.color, _graphic);
      }
      break;
      case NetworkMessages::createOnClick:
      {
        // create On click same as input
        // std::cout << "OnCLick component created" << std::endl;
        EntityId id;
        OnClickComponent onClick;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&onClick, msg.body.data() + sizeof(EntityId),
                    sizeof(OnClickComponent));
        // std::cout << "onClick with id " << id.id << std::endl;
        _componentManager
            .addComponent<component::OnClickComponent>(id.id, onClick.action, onClick.numClient);
        sendAckMessage();
      }
      break;
      case NetworkMessages::createText:
      {
        // std::cout << "Text component created" << std::endl;
        TextComponent text;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&text, msg.body.data() + sizeof(EntityId),
                    sizeof(TextComponent));
        // std::cout << "Text: " << text.x << " " << text.y << " " << text.size << std::endl;
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
        sendAckMessage();
      }
      break;
      case NetworkMessages::updateText:
      {
        // std::cout << "Text component updated" << std::endl;
        TextComponent text;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&text, msg.body.data() + sizeof(EntityId),
                    sizeof(TextComponent));
        // std::cout << "Text: " << text.x << " " << text.y << " " << text.size << std::endl;
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
      }
    }

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
            // std::cout << "Incoming" << std::endl;
            // std::cout << "Size of incoming messages: " << GetIncomingMessages().queueSize() << std::endl;
            rtype::network::Message<NetworkMessages> msg =
                GetIncomingMessages().popFront().message;
            enqueueMessage(msg);
          }
        }
      }
      else
      {
        std::cout << "Server Down" << std::endl;
      }
      while (!msgToSend.empty())
      {
        // popfront the first message in the queue
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

    void ClientSystem::startMessageProcessing()
    {
      processingMessages = true;
      // Launch worker threads
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
                handleMessage(msg); // Process message
            } });
      }
    }

    // Stop processing and join threads
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

    void ClientSystem::enqueueMessage(Message<NetworkMessages> msg)
    {
      {
        std::lock_guard<std::mutex> lock(queueMutex);
        messageQueue.push(std::move(msg));
      }
      queueCondition.notify_one();
    }

    EXPORT_API ECS_system::ISystem *createSystem(component::ComponentManager &componentManager,
                                                 entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic, ECS_system::StringCom stringCom)
    {
      return new rtype::network::ClientSystem(componentManager, entityManager, graphic, stringCom);
    }
  } // namespace network
} // namespace rtype