/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** BackgroundSystem
*/

#include <systems/BackgroundSystem.hpp>

#include <iostream>

void ECS_system::BackgroundSystem::update(
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities) {
  for (auto &entity :
       _componentManager.getEntitiesWithComponents<
           component::ScrollComponent, component::BackgroundComponent,
           component::TransformComponent>(entities)) {
    component::ScrollComponent *scrollComponent =
        _componentManager.getComponent<component::ScrollComponent>(
            entity->getID());
    component::BackgroundComponent *backgroundComponent =
        _componentManager.getComponent<component::BackgroundComponent>(
            entity->getID());
    component::TransformComponent *transformComponent =
        _componentManager.getComponent<component::TransformComponent>(
            entity->getID());

    std::pair <float, float> speed = scrollComponent->getScrollSpeed();
    std::pair <float, float> position = {transformComponent->getPosition().first,
                             transformComponent->getPosition().second};

    position.first -= speed.first * deltaTime;
    if (position.first <= -backgroundComponent->getSize().first ||
        position.first <= -backgroundComponent->getSize().first + speed.first * deltaTime)
      position.first = 0;

    position.second -= speed.second * deltaTime;
    if (position.second <= -backgroundComponent->getSize().second ||
        position.second <= -backgroundComponent->getSize().second + speed.second * deltaTime)
      position.second = 0;

    transformComponent->setPosition(position);
  }
}

EXPORT_API ECS_system::ISystem *
createSystem(component::ComponentManager &componentManager,
             entity::EntityManager &entityManager) {
  return new ECS_system::BackgroundSystem(componentManager, entityManager);
}