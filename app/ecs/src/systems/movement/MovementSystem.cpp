/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MovementSystem
*/

#include <iostream>
#include <systems/MovementSystem.hpp>

/**
 * @brief Updates the positions of entities based on their velocity and the
 * elapsed time.
 *
 * This function iterates through all entities that have both TransformComponent
 * and VelocityComponent. It updates each entity's position by adding the
 * product of its velocity and the elapsed time (deltaTime).
 *
 * @param deltaTime The time elapsed since the last update.
 * @param entities A vector of shared pointers to entities to be updated.
 */
void ECS_system::MovementSystem::update(
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities,
    std::vector<std::pair<std::string, size_t>> &msgToSend, std::vector<std::pair<std::string, size_t>> &msgReceived)
{
  for (auto &entity :
       _componentManager.getEntitiesWithComponents<
           component::TransformComponent, component::VelocityComponent>(
           entities))
  {
    component::TransformComponent *transform =
        _componentManager.getComponent<component::TransformComponent>(
            entity->getID());
    component::VelocityComponent *velocity =
        _componentManager.getComponent<component::VelocityComponent>(
            entity->getID());
    component::TypeComponent *type =
        _componentManager.getComponent<component::TypeComponent>(
            entity->getID());

    float newX = transform->getPosition().first +
                 velocity->getActualVelocity().first * deltaTime;
    float newY = transform->getPosition().second +
                 velocity->getActualVelocity().second * deltaTime;

    if (type->getType() == component::Type::BACKGROUND)
    {
      component::BackgroundComponent *backgroundComponent =
          _componentManager.getComponent<component::BackgroundComponent>(
              entity->getID());

      std::pair<float, float> speed = velocity->getVelocity();
      std::pair<float, float> position = {transform->getPosition().first,
                                          transform->getPosition().second};

      position.first -= speed.first * deltaTime;
      if (position.first <= -backgroundComponent->getSize().first ||
          position.first <=
              -backgroundComponent->getSize().first + speed.first * deltaTime)
        position.first = 0;

      position.second -= speed.second * deltaTime;
      if (position.second <= -backgroundComponent->getSize().second ||
          position.second <=
              -backgroundComponent->getSize().second + speed.second * deltaTime)
        position.second = 0;

      transform->setPosition(position);
    }
    else if (type->getType() == component::Type::PLAYER)
    {
      if (newX < 0)
        newX = 0;
      if (newX > 1920)
        newX = 1920;
      if (newY < 0)
        newY = 0;
      if (newY > 1080)
        newY = 1080;
    }
    else if (type->getType() == component::Type::PROJECTILE)
    {
      if (newX < 0 || newX > 1920 || newY < 0 || newY > 1080)
        _entityManager.removeEntity(entity->getID());
    }
    float subPreviousX = transform->getPreviousPosition().first - newX;
    float subPreviousY = transform->getPreviousPosition().second - newY;
    if (subPreviousX > 5 || subPreviousX < -5 || subPreviousY > 5 ||
        subPreviousY < -5)
    {
      transform->setCommunication(component::ComponentCommunication::UPDATE);
      transform->setPreviousPosition({newX, newY});
      transform->setPosition({newX, newY});
    }
    transform->setPosition({newX, newY});
  }
}

EXPORT_API ECS_system::ISystem *
createSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager)
{
  return new ECS_system::MovementSystem(componentManager, entityManager);
}