/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** RenderSystem
*/

#include "RenderSystem.hpp"

void ECS_system::RenderSystem::update(float deltaTime, std::vector<std::unique_ptr<entity::IEntity>> entities)
{
    window.clear();

    // Get all entities with PositionComponent
    for (auto &entity : _componentManager.getEntitiesWithComponents<component::PositionComponent>(entities))
    {
        // Get PositionComponent
        auto *positionComponent = _componentManager.getComponent<component::PositionComponent>(entity.get()->getID());

        // Draw entity
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(positionComponent->getX(), positionComponent->getY());
        window.draw(shape);
    }
    window.display();
}
