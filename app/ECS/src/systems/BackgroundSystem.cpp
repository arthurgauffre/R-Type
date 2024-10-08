/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** BackgroundSystem
*/

#include "BackgroundSystem.hpp"

#include <iostream>

void ECS_system::BackgroundSystem::update(
    float deltaTime, std::vector<std::shared_ptr<entity::IEntity>> entities) {
  for (auto &entity :
       _componentManager.getEntitiesWithComponents<
           component::ScrollComponent, component::BackgroundComponent,
           component::PositionComponent>(entities)) {
    component::ScrollComponent *scrollComponent =
        _componentManager.getComponent<component::ScrollComponent>(
            entity->getID());
    component::BackgroundComponent *backgroundComponent =
        _componentManager.getComponent<component::BackgroundComponent>(
            entity->getID());
    component::PositionComponent *positionComponent =
        _componentManager.getComponent<component::PositionComponent>(
            entity->getID());

    sf::Vector2f speed = scrollComponent->getScrollSpeed();
    sf::Vector2f position = {positionComponent->getX(),
                             positionComponent->getY()};

    position.x -= speed.x * deltaTime;
    if (position.x <= -backgroundComponent->getSize().x ||
        position.x <= -backgroundComponent->getSize().x + speed.x * deltaTime)
      position.x = 0;

    position.y -= speed.y * deltaTime;
    if (position.y <= -backgroundComponent->getSize().y ||
        position.y <= -backgroundComponent->getSize().y + speed.y * deltaTime)
      position.y = 0;

    positionComponent->setX(position.x);
    positionComponent->setY(position.y);
  }
}