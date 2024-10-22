/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** TransformComponent
*/

#include <components/TransformComponent.hpp>

namespace component {
TransformComponent::TransformComponent(uint32_t entityID, sf::Vector2f position,
                                       sf::Vector2f scale, float rotation)
    : AComponent(entityID), _position(position), _scale(scale),
      _rotation(rotation) {}
} // namespace component
