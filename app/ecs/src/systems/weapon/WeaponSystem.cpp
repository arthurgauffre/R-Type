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

void ECS_system::WeaponSystem::createProjectile(uint32_t parentID,
                                                std::string texturePath,
                                                sf::Vector2f velocity,
                                                sf::Vector2f scale,
                                                int damage) {
  uint32_t projectileID = _entityManager.generateEntityID();
  entity::IEntity *projectile = _entityManager.createEntity(projectileID);

  if (_componentManager.getComponent<component::TypeComponent>(parentID)
          ->getType() == "player")
    _componentManager.addComponent<component::TypeComponent>(
        projectileID, "playerProjectile");
  else
    _componentManager.addComponent<component::TypeComponent>(projectileID,
                                                             "enemyProjectile");
  _componentManager.addComponent<component::DamageComponent>(projectileID,
                                                             damage);
  _componentManager.addComponent<component::ParentComponent>(projectileID,
                                                             parentID);
  _componentManager.addComponent<component::VelocityComponent>(projectileID,
                                                               velocity);
  auto texture = _componentManager.addComponent<component::TextureComponent>(
      projectileID, texturePath);
  _componentManager.addComponent<component::HitBoxComponent>(
      projectileID, texture->getTexture().getSize().x,
      texture->getTexture().getSize().y);

  component::TransformComponent *transformPlayer =
      _componentManager.getComponent<component::TransformComponent>(parentID);
  component::SpriteComponent *spritePlayer =
      _componentManager.getComponent<component::SpriteComponent>(parentID);
  const sf::Texture *texturePlayer = spritePlayer->getSprite().getTexture();

  sf::Vector2f position = {
      transformPlayer->getPosition().x +
          texturePlayer->getSize().x * transformPlayer->getScale().x,
      transformPlayer->getPosition().y +
          (texturePlayer->getSize().y * transformPlayer->getScale().y) / 2};

  if (_componentManager.getComponent<component::TypeComponent>(parentID)
          ->getType() == "enemy")
    position.x -= texturePlayer->getSize().x * transformPlayer->getScale().x;

  component::TransformComponent *transformComponent =
      _componentManager.addComponent<component::TransformComponent>(
          projectileID, position, scale);
  _componentManager.addComponent<component::PositionComponent>(
      projectileID, position.x, position.y);
  _componentManager.addComponent<component::SpriteComponent>(
      projectileID, position.x, position.y);

  if (_componentManager.getComponent<component::TypeComponent>(parentID)
          ->getType() == "enemy")
    transformComponent->setRotation(180);
}

void ECS_system::WeaponSystem::update(
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities) {
  for (auto &entity :
       _componentManager.getEntitiesWithComponents<component::WeaponComponent>(
           entities)) {
    component::WeaponComponent *weaponComponent =
        _componentManager.getComponent<component::WeaponComponent>(
            entity->getID());
    component::CooldownComponent *cooldownComponent =
        _componentManager.getComponent<component::CooldownComponent>(
            weaponComponent->getWeaponEntityID());
    std::string entityType =
        _componentManager
            .getComponent<component::TypeComponent>(entity->getID())
            ->getType();

    if (weaponComponent->getIsFiring() &&
        cooldownComponent->getTimeRemaining() > 0)
      weaponComponent->setIsFiring(false);

    if (cooldownComponent->getTimeRemaining() <= 0 && entityType == "enemy")
      weaponComponent->setIsFiring(true);

    if (weaponComponent->getIsFiring()) {
      sf::Vector2f projectileVelocity = (entityType == "player")
                                            ? sf::Vector2f(200, 0)
                                            : sf::Vector2f(-200, 0);
      this->createProjectile(weaponComponent->getEntityID(),
                             "app/assets/sprites/projectile.gif",
                             projectileVelocity, sf::Vector2f(1, 1), 10);

      cooldownComponent->setTimeRemaining(cooldownComponent->getCooldown());

      if (entityType == "player")
        weaponComponent->setIsFiring(false);
    }
  }

  EXPORT_API ECS_system::ISystem *createSystem(
      component::ComponentManager & componentManager,
      entity::EntityManager & entityManager) {
    return new ECS_system::WeaponSystem(componentManager, entityManager);
  }