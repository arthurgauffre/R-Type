/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** WeaponSystem
*/

#include <iostream>
#include <systems/WeaponSystem.hpp>

ECS_system::WeaponSystem::WeaponSystem(
    component::ComponentManager &componentManager,
    entity::EntityManager &entityManager)
    : ASystem(componentManager, entityManager) {}

ECS_system::WeaponSystem::~WeaponSystem() {}

void ECS_system::WeaponSystem::createProjectile(
    uint32_t parentID, std::string texturePath,
    std::pair<float, float> velocity, std::pair<float, float> scale,
    int damage) {
  std::cout << "Creating projectile" << std::endl;
  uint32_t projectileID = _entityManager.generateEntityID();
  entity::IEntity *projectile = _entityManager.createEntity(projectileID);

  if (_componentManager.getComponent<component::TypeComponent>(parentID)
          ->getType() == component::Type::PLAYER)
    _componentManager.addComponent<component::TypeComponent>(
        projectileID, component::Type::PLAYER_PROJECTILE);
  else
    _componentManager.addComponent<component::TypeComponent>(projectileID,
                                                             component::Type::ENEMY_PROJECTILE);
  _componentManager.addComponent<component::DamageComponent>(projectileID,
                                                             damage);
  _componentManager.addComponent<component::ParentComponent>(projectileID,
                                                             parentID);
  _componentManager.addComponent<component::VelocityComponent>(
      projectileID, velocity, velocity);
  component::TextureComponent *texture = _componentManager.addComponent<component::TextureComponent>(
      projectileID, texturePath);
  _componentManager.addComponent<component::HitBoxComponent>(
      projectileID, texture->getTexture().getSize().x,
      texture->getTexture().getSize().y);

  component::TransformComponent *transformPlayer =
      _componentManager.getComponent<component::TransformComponent>(parentID);
  component::TextureComponent *textureP =
      _componentManager.getComponent<component::TextureComponent>(parentID);
  const sf::Texture *texturePlayer = &textureP->getTexture();

  if (!texturePlayer) {
    std::cout << "Error: Player transform or texture not found" << std::endl;
    return;
  }

  std::pair<float, float> position = {
      transformPlayer->getPosition().first +
          texturePlayer->getSize().x * transformPlayer->getScale().first,
      transformPlayer->getPosition().second +
          (texturePlayer->getSize().y * transformPlayer->getScale().second) /
              2};

  if (_componentManager.getComponent<component::TypeComponent>(parentID)
          ->getType() == component::Type::ENEMY)
    position.first -=
        texturePlayer->getSize().x * transformPlayer->getScale().first;

  component::TransformComponent *transformComponent =
      _componentManager.addComponent<component::TransformComponent>(
          projectileID, position, scale);
  _componentManager.addComponent<component::SpriteComponent>(
      projectileID, position.first, position.second);

  if (_componentManager.getComponent<component::TypeComponent>(parentID)
          ->getType() == component::Type::ENEMY)
    transformComponent->setRotation(180);
}

void ECS_system::WeaponSystem::update(
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities, std::vector<std::pair<std::string, size_t>> &msgToSend, std::vector<std::pair<std::string, size_t>> &msgReceived) {
  for (auto &entity :
       _componentManager.getEntitiesWithComponents<component::WeaponComponent>(
           entities)) {
    component::WeaponComponent *weaponComponent =
        _componentManager.getComponent<component::WeaponComponent>(
            entity->getID());
    component::CooldownComponent *cooldownComponent =
        _componentManager.getComponent<component::CooldownComponent>(
            weaponComponent->getWeaponEntityID());
    component::Type entityType =
        _componentManager
            .getComponent<component::TypeComponent>(entity->getID())
            ->getType();

    if (weaponComponent->getIsFiring() &&
        cooldownComponent->getTimeRemaining() > 0)
      weaponComponent->setIsFiring(false);

    if (cooldownComponent->getTimeRemaining() <= 0 && entityType == component::Type::ENEMY)
      weaponComponent->setIsFiring(true);

    float weaponVelocity = weaponComponent->getVelocity();
    if (weaponComponent->getIsFiring()) {
      std::pair<float, float> projectileVelocity =
          std::pair<float, float>(weaponVelocity, 0);
      this->createProjectile(
          weaponComponent->getEntityID(), "app/assets/sprites/projectile.gif",
          projectileVelocity, std::pair<float, float>(1, 1), 10);

      cooldownComponent->setTimeRemaining(cooldownComponent->getCooldown());

      if (entityType == component::Type::PLAYER) {
        // _componentManager
        //     .getComponent<component::SoundComponent>(
        //         weaponComponent->getWeaponEntityID())
        //     ->setShouldPlay(true);
        weaponComponent->setIsFiring(false);
      }
    }
  }
}

EXPORT_API ECS_system::ISystem *
createSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager) {
  return new ECS_system::WeaponSystem(componentManager, entityManager);
}