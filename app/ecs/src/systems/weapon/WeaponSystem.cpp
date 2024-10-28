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
    entity::EntityManager &entityManager, IGraphic &graphic)
    : ASystem(componentManager, entityManager, graphic) {}

ECS_system::WeaponSystem::~WeaponSystem() {}

void ECS_system::WeaponSystem::createProjectile(
    uint32_t parentID, std::string texturePath,
    std::pair<float, float> velocity, std::pair<float, float> scale,
    int damage) {
  uint32_t projectileID = _entityManager.generateEntityID();
  entity::IEntity *projectile = _entityManager.createEntity(projectileID);

  
  component::TypeComponent *parentTypeComponent = 
      _componentManager.getComponent<component::TypeComponent>(parentID);
  if (parentTypeComponent->getType() == component::Type::PLAYER) {
    _componentManager.addComponent<component::TypeComponent>(
        projectileID, component::Type::PLAYER_PROJECTILE);
  } else {
    _componentManager.addComponent<component::TypeComponent>(
        projectileID, component::Type::ENEMY_PROJECTILE);
  }

  _componentManager.addComponent<component::DamageComponent>(projectileID, damage);
  _componentManager.addComponent<component::ParentComponent>(projectileID, parentID);
  _componentManager.addComponent<component::VelocityComponent>(projectileID, velocity, velocity);

  
  component::TextureComponent *textureComponent = _componentManager.addComponent<component::TextureComponent>(
      projectileID, texturePath, _graphic);
  std::pair<int, int> textureSize = _graphic.getTextureSize(textureComponent->getTextureId());

  _componentManager.addComponent<component::HitBoxComponent>(projectileID, textureSize.first, textureSize.second);

  
  component::TransformComponent *transformParent =
      _componentManager.getComponent<component::TransformComponent>(parentID);
  std::pair<float, float> position = {
      transformParent->getPosition().first + textureSize.first * transformParent->getScale().first,
      transformParent->getPosition().second + (textureSize.second * transformParent->getScale().second) / 2
  };

  if (parentTypeComponent->getType() == component::Type::ENEMY) {
    position.first -= textureSize.first * transformParent->getScale().first;
  }

  component::TransformComponent *transformComponent = _componentManager.addComponent<component::TransformComponent>(
      projectileID, position, scale);
  _componentManager.addComponent<component::SpriteComponent>(projectileID, position.first, position.second, _graphic);

  if (parentTypeComponent->getType() == component::Type::ENEMY) {
    transformComponent->setRotation(180);
  }
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
             entity::EntityManager &entityManager, IGraphic &graphic) {
  return new ECS_system::WeaponSystem(componentManager, entityManager, graphic);
}