/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Position
*/

#include <components/PositionComponent.hpp>

component::PositionComponent::PositionComponent(uint32_t entityID, float x, float y)
      : AComponent(entityID), _x(x), _y(y)
{
}

component::PositionComponent::~PositionComponent()
{
}

float component::PositionComponent::getX() const
{
    return _x;
}

float component::PositionComponent::getY() const
{
    return _y;
}

void component::PositionComponent::update(float deltaTime)
{
}
