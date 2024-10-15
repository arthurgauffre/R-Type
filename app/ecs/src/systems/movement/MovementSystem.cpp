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
    std::vector<std::string> msgToSend) {
  for (auto &entity :
       _componentManager.getEntitiesWithComponents<
           component::TransformComponent, component::VelocityComponent,
           component::PositionComponent>(entities)) {
    auto transform =
        _componentManager.getComponent<component::TransformComponent>(
            entity->getID());
    auto velocity =
        _componentManager.getComponent<component::VelocityComponent>(
            entity->getID());
    auto position =
        _componentManager.getComponent<component::PositionComponent>(
            entity->getID());

    // go to the right of the screen
    float newX = position->getX() + velocity->getVelocity().x * deltaTime;
    float newY = position->getY() + velocity->getVelocity().y * deltaTime;

    transform->setPosition({newX, newY});
    position->setX(newX);
    position->setY(newY);
  }
}

EXPORT_API ECS_system::ISystem *
createSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager) {
  return new ECS_system::MovementSystem(componentManager, entityManager);
}