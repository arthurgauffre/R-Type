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
  entity::IEntity *projectile =
      this->_entityManager.createEntity(_entityManager.generateEntityID());

  this->_componentManager.addComponent<component::TypeComponent>(
      projectile->getID(), "projectile");
  this->_componentManager.addComponent<component::DamageComponent>(
      projectile->getID(), damage);
  this->_componentManager.addComponent<component::ParentComponent>(
      projectile->getID(), parentID);
  this->_componentManager.addComponent<component::VelocityComponent>(
      projectile->getID(), velocity);
  this->_componentManager.addComponent<component::TextureComponent>(
      projectile->getID(), texturePath);

  component::TransformComponent *transformPlayer =
      _componentManager.getComponent<component::TransformComponent>(parentID);
  sf::Vector2f position = {
      transformPlayer->getPosition().x +
          _componentManager.getComponent<component::SpriteComponent>(parentID)
                  ->getSprite()
                  .getTexture()
                  ->getSize()
                  .x *
              transformPlayer->getScale().x,
      transformPlayer->getPosition().y +
          (_componentManager.getComponent<component::SpriteComponent>(parentID)
               ->getSprite()
               .getTexture()
               ->getSize()
               .y *
           transformPlayer->getScale().y) /
              2};
  this->_componentManager.addComponent<component::TransformComponent>(
      projectile->getID(), position, scale);
  this->_componentManager.addComponent<component::PositionComponent>(
      projectile->getID(), position.x, position.y);
  this->_componentManager.addComponent<component::SpriteComponent>(
      projectile->getID(),
      _componentManager.getComponent<component::PositionComponent>(parentID)
          ->getX(),
      _componentManager.getComponent<component::PositionComponent>(parentID)
          ->getY());
}

void ECS_system::WeaponSystem::update(
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities) {
  for (auto &entity :
       _componentManager.getEntitiesWithComponents<component::WeaponComponent>(
           entities)) {
    component::WeaponComponent *weaponComponent =
        _componentManager.getComponent<component::WeaponComponent>(
            entity.get()->getID());
    component::CooldownComponent *cooldownComponent =
        _componentManager.getComponent<component::CooldownComponent>(
            weaponComponent->getWeaponEntityID());

    if (weaponComponent->getIsFiring() == true &&
        cooldownComponent->getTimeRemaining() > 0)
      weaponComponent->setIsFiring(false);

    if (weaponComponent->getIsFiring() == true) {
      this->createProjectile(weaponComponent->getEntityID(),
                             "app/assets/sprites/projectile.gif",
                             sf::Vector2f(200, 0), sf::Vector2f(1, 1), 10);
      cooldownComponent->setTimeRemaining(cooldownComponent->getCooldown());
      weaponComponent->setIsFiring(false);
    }
  }
}

EXPORT_API ECS_system::ISystem *
createSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager) {
  return new ECS_system::WeaponSystem(componentManager, entityManager);
}