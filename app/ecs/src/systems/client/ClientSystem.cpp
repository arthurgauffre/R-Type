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

    // merge it with server
    std::string ClientSystem::GetTexturePath(TexturePath texture)
    {
      switch (texture)
      {
      case TexturePath::Background:
      {
        return "app/assets/images/city_background.png";
      }
      break;
      case TexturePath::Player:
      {
        return "app/assets/sprites/plane.png";
      }
      break;
      case TexturePath::Enemy:
      {
        return "app/assets/sprites/enemy.png";
      }
      break;
      case TexturePath::Bullet:
      {
        return "app/assets/sprites/projectile.gif";
      }
      }
      return "";
    }

    NetworkMessages ClientSystem::getAction(std::string action)
    {
      if (action == "MoveUp")
        return NetworkMessages::moveUp;
      if (action == "MoveDown")
        return NetworkMessages::moveDown;
      if (action == "MoveLeft")
        return NetworkMessages::moveLeft;
      if (action == "MoveRight")
        return NetworkMessages::moveRight;
      if (action == "Shoot")
        return NetworkMessages::shoot;
      return NetworkMessages::none;
    }

    std::string ClientSystem::getStringAction(BindAction action)
    {
      switch (action)
      {
      case BindAction::MoveUp:
        return "MoveUp";
      case BindAction::MoveDown:
        return "MoveDown";
      case BindAction::MoveLeft:
        return "MoveLeft";
      case BindAction::MoveRight:
        return "MoveRight";
      case BindAction::Shoot:
        return "Shoot";
      }
      return "";
    }

    sf::Keyboard::Key ClientSystem::getKey(KeyBoard key)
    {
      switch (key)
      {
      case KeyBoard::A:
        return sf::Keyboard::A;
      case KeyBoard::B:
        return sf::Keyboard::B;
      case KeyBoard::C:
        return sf::Keyboard::C;
      case KeyBoard::D:
        return sf::Keyboard::D;
      case KeyBoard::E:
        return sf::Keyboard::E;
      case KeyBoard::F:
        return sf::Keyboard::F;
      case KeyBoard::G:
        return sf::Keyboard::G;
      case KeyBoard::H:
        return sf::Keyboard::H;
      case KeyBoard::I:
        return sf::Keyboard::I;
      case KeyBoard::J:
        return sf::Keyboard::J;
      case KeyBoard::K:
        return sf::Keyboard::K;
      case KeyBoard::L:
        return sf::Keyboard::L;
      case KeyBoard::M:
        return sf::Keyboard::M;
      case KeyBoard::N:
        return sf::Keyboard::N;
      case KeyBoard::O:
        return sf::Keyboard::O;
      case KeyBoard::P:
        return sf::Keyboard::P;
      case KeyBoard::Q:
        return sf::Keyboard::Q;
      case KeyBoard::R:
        return sf::Keyboard::R;
      case KeyBoard::S:
        return sf::Keyboard::S;
      case KeyBoard::T:
        return sf::Keyboard::T;
      case KeyBoard::U:
        return sf::Keyboard::U;
      case KeyBoard::V:
        return sf::Keyboard::V;
      case KeyBoard::W:
        return sf::Keyboard::W;
      case KeyBoard::X:
        return sf::Keyboard::X;
      case KeyBoard::Y:
        return sf::Keyboard::Y;
      case KeyBoard::Z:
        return sf::Keyboard::Z;
      case KeyBoard::Space:
        return sf::Keyboard::Space;
      }
      return sf::Keyboard::Unknown;
    }

    component::Type ClientSystem::getTypedEntity(EntityType type)
    {
      switch (type)
      {
      case EntityType::Player:
        return component::Type::PLAYER;
      case EntityType::Enemy:
        return component::Type::ENEMY;
      case EntityType::Background:
        return component::Type::BACKGROUND;
      case EntityType::Player_projectile:
        return component::Type::PLAYER_PROJECTILE;
      case EntityType::Enemy_projectile:
        return component::Type::ENEMY_PROJECTILE;
      case EntityType::Projectile:
        return component::Type::PROJECTILE;
      case EntityType::Weapon:
        return component::Type::WEAPON;
      }
      return component::Type::UNKNOWN;
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
      case NetworkMessages::createEntity:
      {
        // std::cout << "Entity created" << std::endl;
        EntityId entity;
        std::memcpy(&entity, msg.body.data(), sizeof(EntityId));

        // std::cout << "Entity id: " << entity.id << std::endl;
        _entityManager.createEntity(entity.id);
      }
      break;
      case NetworkMessages::deleteEntity:
      {
        std::cout << "Entity destroyed" << std::endl;
        EntityId entity;
        std::memcpy(&entity, msg.body.data(), sizeof(EntityId));
        std::cout << "Entity id: " << entity.id << std::endl;
        _componentManager.removeAllComponents(entity.id);
        _entityManager.removeEntity(entity.id);
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
            .addComponent<component::SpriteComponent>(id.id, sprite.x, sprite.y);
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
        _componentManager
            .addComponent<component::TextureComponent>(
                id.id, GetTexturePath(texture.texturePath));
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
      // case NetworkMessages::createMusic:
      // {
      //   std::cout << "Music component created" << std::endl;
      //   MusicComponent music;
      //   EntityId id;
      //   std::memcpy(&id, msg.body.data(), sizeof(EntityId));
      //   std::memcpy(&music, msg.body.data() + sizeof(EntityId),
      //               sizeof(MusicComponent));
      //   std::cout << "Music: " << music.musicPath << std::endl;
      // }
      // break;
      // case NetworkMessages::createSound:
      // {
      //   std::cout << "Sound component created" << std::endl;
      //   SoundComponent sound;
      //   EntityId id;
      //   std::memcpy(&id, msg.body.data(), sizeof(EntityId));
      //   std::memcpy(&sound, msg.body.data() + sizeof(EntityId),
      //               sizeof(SoundComponent));
      //   std::cout << "Sound: " << sound.soundPath << std::endl;
      //   _coreModule.get()->getComponentManager()->addComponent<component::SoundComponent>(id.id,
      //   sound.soundPath);
      // }
      // break;
      case NetworkMessages::createInput:
      {
        // std::cout << "Input component created" << std::endl;
        EntityId id;
        InputComponent input;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&input, msg.body.data() + sizeof(EntityId),
                    sizeof(InputComponent));
        _componentManager.addComponent<component::InputComponent>(id.id, input.numClient);
      }
      break;
      case NetworkMessages::updateInput:
      {
        // std::cout << "Input component updated" << std::endl;
        BindKey input;
        EntityId id;
        std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        std::memcpy(&input, msg.body.data() + sizeof(EntityId),
                    sizeof(BindKey));
        _componentManager
            .updateComponent<component::InputComponent>(id.id, getStringAction(input.action),
                                                        getKey(input.key));
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
            .addComponent<component::TypeComponent>(id.id, getTypedEntity(type.type));
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
            .updateComponent<component::TypeComponent>(id.id, getTypedEntity(type.type));
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
                                                         sprite.y);
      }
      break;
      // case NetworkMessages::updateTexture:
      // {
      //   std::cout << "Texture component updated" << std::endl;
      //   TextureComponent texture;
      //   EntityId id;
      //   std::memcpy(&id, msg.body.data(), sizeof(EntityId));
      //   std::memcpy(&texture, msg.body.data() + sizeof(EntityId),
      //               sizeof(TextureComponent));
      //   std::cout << "Texture: " << GetTexturePath(texture.texturePath)
      //             << std::endl;
      //   _coreModule.get()
      //       ->getComponentManager()
      //       ->updateComponent<component::TextureComponent>(
      //           id.id, GetTexturePath(texture.texturePath));
      // }
      // break;
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
        // break;
        // case NetworkMessages::updateMusic:
        // {
        //   std::cout << "Music component updated" << std::endl;
        //   MusicComponent music;
        //   EntityId id;
        //   std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        //   std::memcpy(&music, msg.body.data() + sizeof(EntityId),
        //               sizeof(MusicComponent));
        //   std::cout << "Music: " << music.musicPath << std::endl;
        // }
        // break;
        // case NetworkMessages::updateSound:
        // {
        //   std::cout << "Sound component updated" << std::endl;
        //   SoundComponent sound;
        //   EntityId id;
        //   std::memcpy(&id, msg.body.data(), sizeof(EntityId));
        //   std::memcpy(&sound, msg.body.data() + sizeof(EntityId),
        //               sizeof(SoundComponent));
        //   std::cout << "Sound: " << sound.soundPath << std::endl;
        //   _coreModule.get()->getComponentManager()->updateComponent<component::SoundComponent>(id.id,
        //   sound.soundPath);
        // }
        // break;
      }
    }

    void ClientSystem::update(float deltaTime,
                              std::vector<std::shared_ptr<entity::IEntity>> entities,
                              std::vector<std::pair<std::string, size_t>> &msgToSend, std::vector<std::pair<std::string, size_t>> &msgReceived, std::mutex &entityMutex)
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
        std::string msg = msgToSend.front().first;
        EntityId id = {msgToSend.front().second};
        msgToSend.erase(msgToSend.begin());
        rtype::network::Message<NetworkMessages> message;
        NetworkMessages action = getAction(msg);
        std::vector<uint8_t> entityBytes(reinterpret_cast<uint8_t *>(&id),
                                         reinterpret_cast<uint8_t *>(&id) +
                                             sizeof(EntityId));
        message.body.insert(message.body.end(), entityBytes.begin(),
                            entityBytes.end());
        if (action != NetworkMessages::none)
        {
          message.header.id = action;
          std::chrono::system_clock::time_point timeNow =
              std::chrono::system_clock::now();
          message << timeNow;
          Send(message);
        }
      }
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
    for (auto &thread : workerThreads) {
        if (thread.joinable()) {
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
                                                 entity::EntityManager &entityManager)
    {
      return new rtype::network::ClientSystem(componentManager, entityManager);
    }
  } // namespace network
} // namespace rtype
