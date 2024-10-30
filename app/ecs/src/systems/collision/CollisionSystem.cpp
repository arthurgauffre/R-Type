/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CollisionSystem
*/

#include <systems/CollisionSystem.hpp>

/**
 * @brief Checks if two hitboxes are colliding.
 *
 * This function determines whether two hitboxes, represented by their
 * respective HitBoxComponent objects, are colliding based on their positions
 * and dimensions.
 *
 * @param hitbox1 A shared pointer to the first HitBoxComponent.
 * @param hitbox2 A shared pointer to the second HitBoxComponent.
 * @return true if the hitboxes are colliding, false otherwise.
 */
bool ECS_system::CollisionSystem::isColliding(
    component::HitBoxComponent *hitbox1, component::HitBoxComponent *hitbox2)
{
  component::TransformComponent *pos1 =
      _componentManager.getComponent<component::TransformComponent>(
          hitbox1->getEntityID());
  component::TransformComponent *pos2 =
      _componentManager.getComponent<component::TransformComponent>(
          hitbox2->getEntityID());

  // Check if the hitboxes are colliding
  if (pos1->getPosition().first <
          pos2->getPosition().first + hitbox2->getWidth() &&
      pos1->getPosition().first + hitbox1->getWidth() >
          pos2->getPosition().first &&
      pos1->getPosition().second <
          pos2->getPosition().second + hitbox2->getHeight() &&
      pos1->getPosition().second + hitbox1->getHeight() >
          pos2->getPosition().second)
    return true;
  return false;
}

/**
 * @brief Handles the collision between two hitboxes.
 *
 * This function is called when a collision is detected between two entities'
 * hitboxes. It processes the collision event and performs necessary actions.
 *
 * @param hitbox1 A shared pointer to the first entity's HitBoxComponent.
 * @param hitbox2 A shared pointer to the second entity's HitBoxComponent.
 */
void ECS_system::CollisionSystem::handleCollision(entity::IEntity *entity1,
                                                  entity::IEntity *entity2)
{
  component::Type type1 =
      _componentManager
          .getComponent<component::TypeComponent>(entity1->getID())
          ->getType();
  component::Type type2 =
      _componentManager
          .getComponent<component::TypeComponent>(entity2->getID())
          ->getType();

  if (type1 == component::Type::PLAYER && type2 == component::Type::ENEMY)
  {
    _componentManager
        .getComponent<component::HealthComponent>(entity1->getID())
        ->setHealth(0);
  }
  else if (type1 == component::Type::ENEMY && type2 == component::Type::PLAYER)
  {
    _componentManager
        .getComponent<component::HealthComponent>(entity2->getID())
        ->setHealth(0);
  }

  if (type1 == component::Type::PLAYER_PROJECTILE && type2 == component::Type::ENEMY)
  {
    int damage = _componentManager.getComponent<component::DamageComponent>(entity1->getID())->getDamage();
    if (!damage)
      damage = 10;
    component::HealthComponent *health = _componentManager
                                             .getComponent<component::HealthComponent>(entity2->getID());
    health->setDamageIncoming(damage);

    entity1->setCommunication(entity::EntityCommunication::DELETE);
  }
  else if (type1 == component::Type::ENEMY && type2 == component::Type::PLAYER_PROJECTILE)
  {
    int damage = _componentManager.getComponent<component::DamageComponent>(entity2->getID())->getDamage();
    if (!damage)
      damage = 10;
    component::HealthComponent *health = _componentManager
                                             .getComponent<component::HealthComponent>(entity1->getID());
    health->setDamageIncoming(damage);

    entity2->setCommunication(entity::EntityCommunication::DELETE);
  }

  if (type1 == component::Type::ENEMY_PROJECTILE && type2 == component::Type::PLAYER)
  {
    int damage = _componentManager.getComponent<component::DamageComponent>(entity1->getID())->getDamage();
    if (!damage)
      damage = 10;
    component::HealthComponent *health = _componentManager
                                             .getComponent<component::HealthComponent>(entity2->getID());
    health->setDamageIncoming(damage);

    entity1->setCommunication(entity::EntityCommunication::DELETE);
  }
  else if (type1 == component::Type::PLAYER && type2 == component::Type::ENEMY_PROJECTILE)
  {
    int damage = _componentManager.getComponent<component::DamageComponent>(entity2->getID())->getDamage();
    if (!damage)
      damage = 10;
    component::HealthComponent *health = _componentManager
                                             .getComponent<component::HealthComponent>(entity1->getID());
    health->setDamageIncoming(damage);

    entity2->setCommunication(entity::EntityCommunication::DELETE);
  }
}

/**
 * @brief Updates the collision system by checking for collisions between
 * entities.
 *
 * This function iterates through a list of entities, retrieves their
 * HitBoxComponents, and checks for collisions between them. If a collision is
 * detected, it handles the collision.
 *
 * @param deltaTime The time elapsed since the last update.
 * @param entities A vector of shared pointers to entities to be checked for
 * collisions.
 */
void ECS_system::CollisionSystem::update(
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities,
    std::vector<std::pair<std::string, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<entity::SceneStatus> &sceneStatus)
{
  for (auto &entity : entities)
  {
    if (entity->getSceneStatus() != *sceneStatus)
      continue;
    component::HitBoxComponent *hitbox1 =
        _componentManager.getComponent<component::HitBoxComponent>(
            entity->getID());

    if (hitbox1 == nullptr)
      continue;
    for (auto &entity2 : entities)
    {
      component::HitBoxComponent *hitbox2 =
          _componentManager.getComponent<component::HitBoxComponent>(
              entity2->getID());

      if (hitbox2 == nullptr)
        continue;
      if (hitbox1->getEntityID() == hitbox2->getEntityID())
        continue;
      if (isColliding(hitbox1, hitbox2))
        handleCollision(entity.get(), entity2.get());
    }
  }
}

EXPORT_API ECS_system::ISystem *
createSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager)
{
  return new ECS_system::CollisionSystem(componentManager, entityManager);
}