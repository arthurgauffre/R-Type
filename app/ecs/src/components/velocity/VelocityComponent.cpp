/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** VelocityComponent
*/

#include <components/VelocityComponent.hpp>

namespace component {
VelocityComponent::VelocityComponent(uint32_t entityID, sf::Vector2f velocity)
    : AComponent(entityID), _velocity(velocity) {}
} // namespace component