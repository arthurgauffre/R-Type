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
    std::vector<std::pair<Action, size_t>> &msgToSend, std::vector<std::pair<std::string, std::pair<size_t, size_t>>> &msgReceived, std::mutex &entityMutex, std::shared_ptr<Scene> &sceneStatus)
{
  std::lock_guard<std::mutex> lock(entityMutex);
  for (auto &entity :
       _componentManager.getEntitiesWithComponents<
           component::TransformComponent, component::VelocityComponent>(
           entities))
  {
    if (entity->getSceneStatus() != *sceneStatus && entity->getSceneStatus() != Scene::ALL)
      continue;
    component::TransformComponent *transform =
        _componentManager.getComponent<component::TransformComponent>(
            entity->getID());
    component::VelocityComponent *velocity =
        _componentManager.getComponent<component::VelocityComponent>(
            entity->getID());
    component::TypeComponent *type =
        _componentManager.getComponent<component::TypeComponent>(
            entity->getID());

    if (!transform || !velocity || !type)
      return;

    float newX = transform->getPosition().first +
                 velocity->getActualVelocity().first * deltaTime;
    float newY = transform->getPosition().second +
                 velocity->getActualVelocity().second * deltaTime;

    if (type->getType() == Type::BACKGROUND)
    {
      component::SizeComponent *size =
          _componentManager.getComponent<component::SizeComponent>(
              entity->getID());

      if (!size)
        return;
      if (newX < -size->getSize().first)
        newX = size->getSize().first - 1;
      if (newX > size->getSize().first)
        newX = -size->getSize().first + 1;
      if (newY < -size->getSize().second)
        newY = size->getSize().second - 1;
      if (newY > size->getSize().second)
        newY = -size->getSize().second + 1;
    }
    else if (type->getType() == Type::PLAYER)
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
    else if (type->getType() == Type::ENEMY_PROJECTILE ||
             type->getType() == Type::PLAYER_PROJECTILE)
    {
      if (newX < 0 || newX > 1920 || newY < 0 || newY > 1080)
        entity->setCommunication(entity::EntityCommunication::DELETE);
    }
    float subPreviousX = transform->getPreviousPosition().first - newX;
    float subPreviousY = transform->getPreviousPosition().second - newY;
    if (subPreviousX > 5 || subPreviousX < -5 || subPreviousY > 5 ||
        subPreviousY < -5)
    {
      transform->setCommunication(component::ComponentCommunication::UPDATE);
      transform->setPreviousPosition({newX, newY});
    }
    transform->setPosition({newX, newY});
    if (type->getType() == Type::ENEMY)
    {
      if (newX < -200 || newX > 2200 || newY < -100 || newY > 1350)
        entity->setCommunication(entity::EntityCommunication::DELETE);
    }
  }
}

/**
 * @brief Factory function to create a MovementSystem instance.
 *
 * This function creates and returns a new instance of the MovementSystem class.
 *
 * @param componentManager Reference to the ComponentManager instance.
 * @param entityManager Reference to the EntityManager instance.
 * @param graphic Shared pointer to an IGraphic instance.
 * @param stringCom StringCom instance for communication.
 * @return Pointer to the newly created MovementSystem instance.
 */
EXPORT_API ECS_system::ISystem *
createSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager, std::shared_ptr<IGraphic> graphic, std::shared_ptr<IAudio> audio, ECS_system::StringCom stringCom)
{
  return new ECS_system::MovementSystem(componentManager, entityManager, graphic, audio, stringCom);
}