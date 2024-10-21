/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ClientSystem
*/

#include <systems/ClientSystem.hpp>

namespace rtype {
namespace network {

// merge it with server
std::string ClientSystem::GetTexturePath(TexturePath texture) {
  switch (texture) {
  case TexturePath::Background: {
    return "app/assets/images/city_background.png";
  } break;
  case TexturePath::Player: {
    return "app/assets/sprites/plane.png";
  } break;
    // case TexturePath::Enemy:
    // return "assets/enemy.png";
  }
  return "";
}

KeyAction ClientSystem::getAction(std::string action) {
  if (action == "moveUp")
    return KeyAction::moveUp;
  if (action == "moveDown")
    return KeyAction::moveDown;
  if (action == "moveLeft")
    return KeyAction::moveLeft;
  if (action == "moveRight")
    return KeyAction::moveRight;
  if (action == "shoot")
    return KeyAction::shoot;
  return KeyAction::moveUp;
}

void ClientSystem::handdleMessage(
    rtype::network::Message<NetworkMessages> &msg) {
  switch (msg.header.id) {
  case NetworkMessages::ServerAcceptance: {
    std::cout << "Server Accepted Connection" << std::endl;
  } break;

  case NetworkMessages::ServerPing: {
    std::chrono::system_clock::time_point timeNow =
        std::chrono::system_clock::now();
    std::chrono::system_clock::time_point timeThen;
    msg >> timeThen;
    std::cout << "Ping: "
              << std::chrono::duration<double>(timeNow - timeThen).count()
              << std::endl;
  } break;
  case NetworkMessages::ServerMessage: {
    uint32_t clientID;
    msg >> clientID;
    std::cout << "Hello from [" << clientID << "]" << std::endl;
  } break;
  case NetworkMessages::ServerDenial: {
  } break;
  case NetworkMessages::MessageAll: {
  } break;
  case NetworkMessages::ClientConnection: {
  } break;
  case NetworkMessages::createEntity: {
    std::cout << "Entity created" << std::endl;
    EntityId entity;
    std::memcpy(&entity, msg.body.data(), sizeof(EntityId));

    std::cout << "Entity id: " << entity.id << std::endl;
    _entityManager.createEntity(entity.id);
  } break;
  case NetworkMessages::deleteEntity: {
    std::cout << "Entity destroyed" << std::endl;
    EntityId entity;
    std::memcpy(&entity, msg.body.data(), sizeof(EntityId));
    std::cout << "Entity id: " << entity.id << std::endl;
    _entityManager.destroyEntity(entity.id);
  } break;
  case NetworkMessages::createPosition: {
    std::cout << "Position component created" << std::endl;
    PositionComponent pos;
    EntityId id;
    std::memcpy(&id, msg.body.data(), sizeof(EntityId));
    std::memcpy(&pos, msg.body.data() + sizeof(EntityId),
                sizeof(PositionComponent));
    std::cout << "Position: " << pos.x << " " << pos.y << std::endl;
    _componentManager.addComponent<component::PositionComponent>(id.id, pos.x,
                                                                 pos.y);
  } break;
  case NetworkMessages::createSprite: {
    std::cout << "Sprite component created" << std::endl;
    SpriteComponent sprite;
    EntityId id;
    std::memcpy(&id, msg.body.data(), sizeof(EntityId));
    std::memcpy(&sprite, msg.body.data() + sizeof(EntityId),
                sizeof(SpriteComponent));
    std::cout << "Sprite: " << sprite.x << " " << sprite.y << std::endl;
    _componentManager.addComponent<component::SpriteComponent>(id.id, sprite.x,
                                                               sprite.y);
  } break;
  case NetworkMessages::createTexture: {
    std::cout << "Texture component created" << std::endl;
    TextureComponent texture;
    EntityId id;
    std::memcpy(&id, msg.body.data(), sizeof(EntityId));
    std::memcpy(&texture, msg.body.data() + sizeof(EntityId),
                sizeof(TextureComponent));
    _componentManager.addComponent<component::TextureComponent>(
        id.id, GetTexturePath(texture.texturePath));
  } break;
  case NetworkMessages::createTransform: {
    std::cout << "Transform component created" << std::endl;
    TransformComponent transform;
    EntityId id;
    std::memcpy(&id, msg.body.data(), sizeof(EntityId));
    std::memcpy(&transform, msg.body.data() + sizeof(EntityId),
                sizeof(TransformComponent));
    std::cout << "Transform: " << transform.x << " " << transform.y << " "
              << transform.scaleX << " " << transform.scaleY << std::endl;
    _componentManager.addComponent<component::TransformComponent>(
        id.id, sf::Vector2f(transform.x, transform.y),
        sf::Vector2f(transform.scaleX, transform.scaleY));
  } break;
  case NetworkMessages::createBackground: {
    std::cout << "Background component created" << std::endl;
    BackgroundComponent background;
    EntityId id;
    std::memcpy(&id, msg.body.data(), sizeof(EntityId));
    std::memcpy(&background, msg.body.data() + sizeof(EntityId),
                sizeof(BackgroundComponent));
    std::cout << "Background: " << background.x << " " << background.y
              << std::endl;
    std::cout << "Texture: " << GetTexturePath(background.texturePath)
              << std::endl;
    _componentManager.addComponent<component::BackgroundComponent>(
        id.id, GetTexturePath(background.texturePath),
        sf::Vector2f(background.x, background.y));
  } break;
  case NetworkMessages::createVelocity: {
    std::cout << "Velocity component created" << std::endl;
    VelocityComponent velocity;
    EntityId id;
    std::memcpy(&id, msg.body.data(), sizeof(EntityId));
    std::memcpy(&velocity, msg.body.data() + sizeof(EntityId),
                sizeof(VelocityComponent));
    std::cout << "Velocity: " << velocity.x << " " << velocity.y << std::endl;
    _componentManager.addComponent<component::VelocityComponent>(
        id.id, sf::Vector2f(velocity.x, velocity.y));
  } break;
  case NetworkMessages::createParent: {
    std::cout << "Parent component created" << std::endl;
    ParentComponent parent;
    EntityId id;
    std::memcpy(&id, msg.body.data(), sizeof(EntityId));
    std::memcpy(&parent, msg.body.data() + sizeof(EntityId),
                sizeof(ParentComponent));
    std::cout << "Parent: " << parent.parentID << std::endl;
    _componentManager.addComponent<component::ParentComponent>(id.id,
                                                               parent.parentID);
  } break;
  case NetworkMessages::createScroll: {
    std::cout << "Scroll component created" << std::endl;
    ScrollComponent scroll;
    EntityId id;
    std::memcpy(&id, msg.body.data(), sizeof(EntityId));
    std::memcpy(&scroll, msg.body.data() + sizeof(EntityId),
                sizeof(ScrollComponent));
    std::cout << "Scroll: " << scroll.x << " " << scroll.y << std::endl;
    _componentManager.addComponent<component::ScrollComponent>(
        id.id, sf::Vector2f(scroll.x, scroll.y));
  } break;
  case NetworkMessages::createHealth: {
    std::cout << "Health component created" << std::endl;
    HealthComponent health;
    EntityId id;
    std::memcpy(&id, msg.body.data(), sizeof(EntityId));
    std::memcpy(&health, msg.body.data() + sizeof(EntityId),
                sizeof(HealthComponent));
    std::cout << "Health: " << health.health << std::endl;
    _componentManager.addComponent<component::HealthComponent>(id.id,
                                                               health.health);
  } break;
  case NetworkMessages::createDamage: {
    std::cout << "Damage component created" << std::endl;
    DamageComponent damage;
    EntityId id;
    std::memcpy(&id, msg.body.data(), sizeof(EntityId));
    std::memcpy(&damage, msg.body.data() + sizeof(EntityId),
                sizeof(DamageComponent));
    std::cout << "Damage: " << damage.damage << std::endl;
    _componentManager.addComponent<component::DamageComponent>(id.id,
                                                               damage.damage);
  } break;
  case NetworkMessages::createHitbox: {
    std::cout << "Hitbox component created" << std::endl;
    HitboxComponent hitbox;
    EntityId id;
    std::memcpy(&id, msg.body.data(), sizeof(EntityId));
    std::memcpy(&hitbox, msg.body.data() + sizeof(EntityId),
                sizeof(HitboxComponent));
    std::cout << "Hitbox: " << hitbox.x << " " << hitbox.y << std::endl;
    _componentManager.addComponent<component::HitBoxComponent>(id.id, hitbox.x,
                                                               hitbox.y);
  } break;
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
  case NetworkMessages::updatePosition: {
    std::cout << "Position component updated" << std::endl;
    PositionComponent pos;
    EntityId id;
    std::memcpy(&id, msg.body.data(), sizeof(EntityId));
    std::memcpy(&pos, msg.body.data() + sizeof(EntityId),
                sizeof(PositionComponent));
    std::cout << "Position: " << pos.x << " " << pos.y << std::endl;
    _componentManager.updateComponent<component::PositionComponent>(
        id.id, pos.x, pos.y);
  } break;
  case NetworkMessages::updateSprite: {
    std::cout << "Sprite component updated" << std::endl;
    SpriteComponent sprite;
    EntityId id;
    std::memcpy(&id, msg.body.data(), sizeof(EntityId));
    std::memcpy(&sprite, msg.body.data() + sizeof(EntityId),
                sizeof(SpriteComponent));
    std::cout << "Sprite: " << sprite.x << " " << sprite.y << std::endl;
    _componentManager.updateComponent<component::SpriteComponent>(
        id.id, sprite.x, sprite.y);
  } break;
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
  case NetworkMessages::updateTransform: {
    std::cout << "Transform component updated" << std::endl;
    TransformComponent transform;
    EntityId id;
    std::memcpy(&id, msg.body.data(), sizeof(EntityId));
    std::memcpy(&transform, msg.body.data() + sizeof(EntityId),
                sizeof(TransformComponent));
    std::cout << "Transform: " << transform.x << " " << transform.y << " "
              << transform.scaleX << " " << transform.scaleY << std::endl;
    _componentManager.updateComponent<component::TransformComponent>(
        id.id, sf::Vector2f(transform.x, transform.y),
        sf::Vector2f(transform.scaleX, transform.scaleY));
  } break;
  // case NetworkMessages::updateBackground:
  // {
  //   std::cout << "Background component updated" << std::endl;
  //   BackgroundComponent background;
  //   EntityId id;
  //   std::memcpy(&id, msg.body.data(), sizeof(EntityId));
  //   std::memcpy(&background, msg.body.data() + sizeof(EntityId),
  //               sizeof(BackgroundComponent));
  //   std::cout << "Background: " << background.x << " " << background.y
  //             << std::endl;
  //   std::cout << "Texture: " << GetTexturePath(background.texturePath)
  //             << std::endl;
  //   _coreModule.get()
  //       ->getComponentManager()
  //       ->updateComponent<component::BackgroundComponent>(
  //           id.id, GetTexturePath(background.texturePath),
  //           sf::Vector2f(background.x, background.y));
  // }
  // break;
  case NetworkMessages::updateVelocity: {
    std::cout << "Velocity component updated" << std::endl;
    VelocityComponent velocity;
    EntityId id;
    std::memcpy(&id, msg.body.data(), sizeof(EntityId));
    std::memcpy(&velocity, msg.body.data() + sizeof(EntityId),
                sizeof(VelocityComponent));
    std::cout << "Velocity: " << velocity.x << " " << velocity.y << std::endl;
    _componentManager.updateComponent<component::VelocityComponent>(
        id.id, sf::Vector2f(velocity.x, velocity.y));
  } break;
  case NetworkMessages::updateParent: {
    std::cout << "Parent component updated" << std::endl;
    ParentComponent parent;
    EntityId id;
    std::memcpy(&id, msg.body.data(), sizeof(EntityId));
    std::memcpy(&parent, msg.body.data() + sizeof(EntityId),
                sizeof(ParentComponent));
    std::cout << "Parent: " << parent.parentID << std::endl;
    _componentManager.updateComponent<component::ParentComponent>(
        id.id, parent.parentID);
  } break;
  case NetworkMessages::updateScroll: {
    std::cout << "Scroll component updated" << std::endl;
    ScrollComponent scroll;
    EntityId id;
    std::memcpy(&id, msg.body.data(), sizeof(EntityId));
    std::memcpy(&scroll, msg.body.data() + sizeof(EntityId),
                sizeof(ScrollComponent));
    std::cout << "Scroll: " << scroll.x << " " << scroll.y << std::endl;
    _componentManager.updateComponent<component::ScrollComponent>(
        id.id, sf::Vector2f(scroll.x, scroll.y));
  } break;
  case NetworkMessages::updateHealth: {
    std::cout << "Health component updated" << std::endl;
    HealthComponent health;
    EntityId id;
    std::memcpy(&id, msg.body.data(), sizeof(EntityId));
    std::memcpy(&health, msg.body.data() + sizeof(EntityId),
                sizeof(HealthComponent));
    std::cout << "Health: " << health.health << std::endl;
    _componentManager.updateComponent<component::HealthComponent>(
        id.id, health.health);
  } break;
  case NetworkMessages::updateDamage: {
    std::cout << "Damage component updated" << std::endl;
    DamageComponent damage;
    EntityId id;
    std::memcpy(&id, msg.body.data(), sizeof(EntityId));
    std::memcpy(&damage, msg.body.data() + sizeof(EntityId),
                sizeof(DamageComponent));
    std::cout << "Damage: " << damage.damage << std::endl;
    _componentManager.updateComponent<component::DamageComponent>(
        id.id, damage.damage);
  } break;
  case NetworkMessages::updateHitbox: {
    std::cout << "Hitbox component updated" << std::endl;
    HitboxComponent hitbox;
    EntityId id;
    std::memcpy(&id, msg.body.data(), sizeof(EntityId));
    std::memcpy(&hitbox, msg.body.data() + sizeof(EntityId),
                sizeof(HitboxComponent));
    std::cout << "Hitbox: " << hitbox.x << " " << hitbox.y << std::endl;
    _componentManager.updateComponent<component::HitBoxComponent>(
        id.id, hitbox.x, hitbox.y);
  }
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

std::vector<std::string>
ClientSystem::update(float deltaTime,
                     std::vector<std::shared_ptr<entity::IEntity>> entities,
                     std::vector<std::string> msgToSend) {
  if (IsConnected()) {
    if (!GetIncomingMessages().empty()) {
      std::cout << "Incoming" << std::endl;
      rtype::network::Message<NetworkMessages> msg =
          GetIncomingMessages().popFront().message;
      handdleMessage(msg);
    }
  } else {
    std::cout << "Server Down" << std::endl;
  }
  return msgToSend;
}

EXPORT_API ECS_system::ISystem *
createSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager) {
  return new rtype::network::ClientSystem(componentManager, entityManager);
}
} // namespace network
} // namespace rtype
