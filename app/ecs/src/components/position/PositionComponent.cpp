/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Position
*/

#include <components/PositionComponent.hpp>

component::PositionComponent::PositionComponent(uint32_t entityID, float x,
                                                float y) : AComponent(entityID)
{
    _position.x = x;
    _position.y = y;
}
